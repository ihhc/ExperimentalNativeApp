#include <iostream>
#include <string>
#include <pqxx\pqxx>

using namespace std;

int main()
{
	string conn = "host=localhost port=5432 dbname=TestDB user=postgres password=postgres";
	try
	{
		pqxx::connection connectionObject(conn.c_str());
		pqxx::work pqworking(connectionObject);
		pqxx::result res = pqworking.exec("SELECT * FROM TestTable");
		for (int i = 0; res.size(); i++)
			cout << res[i][0] << "	" << res[i][1];

	}
	catch (exception& e)
	{
		cout << e.what();
	}
	return 0;;
}


