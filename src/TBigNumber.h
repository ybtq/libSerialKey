#ifndef _TBIGNUMBER_H_
#define _TBIGNUMBER_H_

#include <deque>
#include <string>

class TBigNumber
{
public:
    TBigNumber(unsigned int number = 0);

    TBigNumber&     operator = (unsigned int number);
    TBigNumber&     operator+= (unsigned int number);
    TBigNumber&     operator+= (const TBigNumber& other);
    TBigNumber      operator / (unsigned int dividend);
    TBigNumber&     operator/= (unsigned int dividend);
    TBigNumber      operator * (unsigned int multiplicand);
    TBigNumber&     operator*= (unsigned int multiplicand);
    unsigned int    operator % (unsigned int dividend);
    bool            operator>= (unsigned int other);

    std::string     ToString();
    void            FromString(const std::string& sText);
    void            FromPowof(unsigned int base, unsigned int exp);

private:
    std::deque<unsigned char>    mData;
};

#endif // _TBIGNUMBER_H_
