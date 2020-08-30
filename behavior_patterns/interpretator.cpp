
#include <iostream>

class Expression
{
public:
	virtual ~Expression() {}
	virtual double evaluate() = 0;
};

class NumberExpression : public Expression
{
public:
	NumberExpression(double value)
		: value_(value)
	{}

	virtual double evaluate()
	{
		return value_;
	}

private:
	double value_;
};

class AdditionExpression : public Expression
{
public:
	AdditionExpression(Expression* left, Expression* right)
		: left_(left), right_(right)
	{}

	virtual double evaluate()
	{
		//Calculate operands
		double left = left_->evaluate();
		double right = right_->evaluate();

		//Add them
		return left + right;
	}

private:
	Expression* left_;
	Expression* right_;
};