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
		NONE,
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
	Bracket(const string& str, int i) : m_type(NONE), m_side(LEFT), m_index(i)
	{
		if (str == "(")
		{
			m_type = PARENTHESE;
			m_side = LEFT;
		}
		else if (str == ")")
		{
			m_type = PARENTHESE;
			m_side = RIGHT;
		}
		else if (str == "[")
		{
			m_type = SQUARE;
			m_side = LEFT;
		}
		else if (str == "]")
		{
			m_type = SQUARE;
			m_side = RIGHT;
		}
		else if (str == "{")
		{
			m_type = BRACES;
			m_side = LEFT;
		}
		else if (str == "}")
		{
			m_type = BRACES;
			m_side = RIGHT;
		}
		else if (str == "<")
		{
			m_type = ANGLE;
			m_side = LEFT;
		}
		else if (str == ">")
		{
			m_type = ANGLE;
			m_side = RIGHT;
		}
		else if (str == "(*")
		{
			m_type = STAR;
			m_side = LEFT;
		}
		else if (str == "*)")
		{
			m_type = STAR;
			m_side = RIGHT;
		}
	}
	
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
	size_t counter = 0;
	for (string::const_iterator iter = str.begin(); iter != str.end(); iter++)
	{
		if (*iter == '*')
		{
			if (!brackets.empty() && brackets.back().get_type() == Bracket::type::PARENTHESE && brackets.back().get_side() == Bracket::side::LEFT)
			{
				Bracket b("(*", counter);
				brackets.back() = b;
			}
			else if (iter + 1 != str.end() && *(iter + 1) == ')')
			{
				Bracket b("*)", ++counter);
				brackets.push_back(b);
				iter++;
			}
			continue;
		}

		string s;
		s.push_back(*iter);
		Bracket b(s, ++counter);
		if (b.get_type() != Bracket::type::NONE)
		{
			brackets.push_back(b);
		}
	}
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
			if (left_brackets.empty() || !brackets[i].is_match(left_brackets.top()))
			{
				return make_tuple(false, brackets[i].get_index());
			}
			else
			{
				left_brackets.pop();
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
