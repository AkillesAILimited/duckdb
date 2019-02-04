#include "catch.hpp"
#include "test_helpers.hpp"

using namespace duckdb;
using namespace std;

TEST_CASE("Test LIMIT keyword", "[limit]") {
	unique_ptr<DuckDBResult> result;
	DuckDB db(nullptr);
	DuckDBConnection con(db);
	con.EnableQueryVerification();

	REQUIRE_NO_FAIL(con.Query("CREATE TABLE test (a INTEGER, b INTEGER);"));
	REQUIRE_NO_FAIL(con.Query("INSERT INTO test VALUES (11, 22), (12, 21), (13, 22)"));

	// constant limit
	result = con.Query("SELECT a FROM test LIMIT 1");
	REQUIRE(CHECK_COLUMN(result, 0, {11}));

	// decimal limit
	result = con.Query("SELECT a FROM test LIMIT 1.5");
	REQUIRE(CHECK_COLUMN(result, 0, {11}));

	// LIMIT with operation
	result = con.Query("SELECT a FROM test LIMIT 2-1");
	REQUIRE(CHECK_COLUMN(result, 0, {11}));

	// LIMIT with non-scalar should fail
	REQUIRE_FAIL(con.Query("SELECT a FROM test LIMIT a"));
	// LIMIT with non-scalar operation should also fail
	REQUIRE_FAIL(con.Query("SELECT a FROM test LIMIT a+1"));
}
