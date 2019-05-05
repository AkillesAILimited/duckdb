//===----------------------------------------------------------------------===//
//                         DuckDB
//
// execution/index/art/node16.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once
#import "node.hpp"

namespace duckdb {

class Node16 : public Node {
public:
	uint8_t key[16];
	Node *child[16];

	Node16() : Node(NodeType::N16,this->maxPrefixLength) {
		memset(key, 0, sizeof(key));
		memset(child, 0, sizeof(child));
	}
	Node **getChild(const uint8_t k);

	//! Insert leaf into inner node
	void static insert(Node16 *node, Node **nodeRef, uint8_t keyByte, Node *child);
};
} // namespace duckdb
