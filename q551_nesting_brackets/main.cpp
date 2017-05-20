#include <iostream>
#include <string>
#include <tuple>

using namespace std;

tuple<bool, int> evaluate_brackets(const string& input)
{
	return make_tuple(true, 0);
}

void main()
{
	string line;
	while(getline(cin, line))
	{
		bool nested = false;
		int error_index = 0;
		tie(nested, error_index) = evaluate_brackets(line);

		if (nested)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO " << error_index << endl;
		}
	}
}
