#include <stdexcept>
#include "rational.h"
#include <cmath>

using namespace std;

Rational::Rational()
{
    n = 0;
    d = 1;
}
Rational::Rational(int num, int denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    // Continue your implementation below.
    // You should likely call this->reduce() and this->normalize0()
    n = num;
    d = denom;

    this -> handleSigns();
    this-> reduce();
    this -> normalize0();
   
}

void Rational::reduce()
{
	int divisor = gcd(n, d);
	n /= divisor;
	d /= divisor;
}

ostream& operator<<(ostream &ostr, const Rational &r){

	Rational temp;
	temp.n = r.n;
	temp.d = r.d;
	temp.reduce();
	temp.handleSigns();
	temp.normalize0();

	ostr << temp.n << "/" << temp.d;
	return ostr;
}

istream& operator>>(istream &istr, Rational &r){

	char throwaway = ' ';
	istr >> r.n;
	istr >> throwaway;
	istr >> r.d;

	r.handleSigns();
	r.reduce();

	return istr;
}


Rational Rational::operator+(const Rational &rhs){

	Rational temp;
	int multiple = lcm(d, rhs.d);
	temp.d = multiple;
	temp.n = multiple/d * n + multiple/rhs.d * rhs.n;


	return temp;
}

Rational Rational::operator+(const int &rhs){

	Rational temp;
	temp.d = d;
	temp.n = rhs*d + n;
	return temp;
}

Rational operator+(const int &lhs, const Rational &rhs)
{
	Rational temp;

	temp.d = rhs.d;
	temp.n = lhs*rhs.d + rhs.n;

	return temp;
}

Rational Rational::operator*(const Rational &rhs)
{
	Rational temp;
	temp.d = d * rhs.d;
	temp.n= n * rhs.n;
	return temp;

}

Rational Rational::operator*(const int &rhs)
{
	Rational temp;
	temp.n = n *rhs;
	temp.d = d;
	return temp;
}

Rational operator*(const int &lhs, const Rational &rhs)
{
	Rational temp;
	temp.d = rhs.d;
	temp.n = rhs.n * lhs;
	return temp;
}

Rational Rational::operator^(const int &rhs)
{
	Rational temp;

	if(rhs < 0){
		temp.n = (int)(pow((double)(d), abs(rhs)));
		temp.d = (int)(pow((double)(n), abs(rhs)));
	}
	else{
		temp.n = (int)(pow((double)(n), rhs));
		temp.d = (int)(pow((double)(d), rhs));
	}

	return temp;
}

bool Rational::operator==(const Rational &rhs)
{
	return (n == rhs.n && d == rhs.d);
}

bool Rational::operator!=(const Rational &rhs)
{

	return (n != rhs.n || d != rhs.d);
}

bool Rational::operator<(const Rational &rhs)
{
	return ((double)(n)/ (d) < (double)(rhs.n)/(rhs.d));
}


Rational& Rational::operator+=(const Rational &rhs)
{
	int multiple = lcm(d, rhs.d);
	this->n = n * multiple/d + rhs.n * multiple/rhs.d;
	this->d = multiple;

	return *this;
}

Rational& Rational::operator+=(const int &rhs)
{
	this->n = n + rhs*d;

	return *this;

}

Rational& Rational::operator*=(const Rational &rhs)
{
	this->n = n* rhs.n;
	this->d = d* rhs.d;

	return *this;
}

Rational& Rational::operator*=(const int &rhs)
{
	this->n = n* rhs;

	return *this;
}


int Rational::gcd(int a, int b)
{
	int least = 0;
	int divisor = 0;
	if(abs(a) > abs(b))
		least = abs(b);
	else
		least = abs(a);

	if(least == 0)
		return 1;

	for(int i = 1; i < least +1; i++){
		if(a%i == 0 && b%i == 0)
			divisor = i;
	}
	return divisor;
}

int Rational::lcm(int a, int b)
{
	int divisor = gcd(a, b);
	return (a*b/divisor);

}



void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1;
}

void Rational::handleSigns()
{
	if(d < 0){
		if(n < 0){
			d = abs(d);
			n = abs(n);
		}

		else{
			d = abs(d);
			n = n * -1;
		}
	}
}

