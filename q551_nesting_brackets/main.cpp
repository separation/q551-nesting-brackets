#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <stack>

using namespace std;

class Bracket
{
public:
	enum type
	{
		PARENTHESE, // ()
		SQUARE, // []
		BRACES, // {}
		ANGLE, // <>
		STAR, // (**)
	};

	enum side
	{
		LEFT,
		RIGHT,
	};

public:
	Bracket(const type& t, const side& s, int i) : m_type(t), m_side(s), m_index(i) {}
	
	bool is_match(const Bracket& b)
	{
		return b.get_type() == m_type && b.get_side() != m_side;
	}

	type get_type() const { return m_type; };
	side get_side() const { return m_side; };
	int get_index() const { return m_index; };

private:
	type m_type;
	side m_side;
	int m_index;
};

vector<Bracket> to_brackets(const string& str)
{
	vector<Bracket> brackets;
	return brackets;
}

tuple<bool, int> evaluate_brackets(const string& input)
{
	vector<Bracket> brackets = to_brackets(input);

	if (brackets.size() == 0)
	{
		return make_tuple(true, 0);
	}

	stack<Bracket> left_brackets;	
	for (size_t i = 0; i < brackets.size(); i++)
	{
		if (brackets[i].get_side() == Bracket::side::LEFT)
		{
			left_brackets.push(brackets[i]);
		}
		else
		{
			if (brackets[i].is_match(left_brackets.top()))
			{
				left_brackets.pop();
			}
			else
			{
				return make_tuple(false, brackets[i].get_index());
			}
		}
	}

	if (left_brackets.empty())
	{
		return make_tuple(true, 0);
	}
	else
	{
		return make_tuple(false, left_brackets.top().get_index());
	}
	
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
