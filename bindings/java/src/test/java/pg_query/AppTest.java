package pg_query;

import static org.junit.Assert.assertTrue;

import org.junit.Test;

/**
 * Unit test for simple App.
 */
public class AppTest {
		static {
				System.loadLibrary("pg_query");
		}

		/**
		 * Rigorous Test :-)
		 */
		@Test
		public void shouldAnswerWithTrue () {
				System.out.println(PgQuery.pg_query_parse("select 1"));
				assertTrue( true );
		}
}
