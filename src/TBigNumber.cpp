#include <string.h>
#include "TBigNumber.h"

static unsigned char RADIX = 10;

TBigNumber::TBigNumber(unsigned int number)
{
    *this = number;
}

TBigNumber& TBigNumber::operator = (unsigned int number)
{
    mData.clear();
    while (number > 0)
    {
        mData.push_front(number % RADIX);
        number /= RADIX;
    }
    return *this;
}

TBigNumber& TBigNumber::operator += (unsigned int number)
{
    unsigned char carry = 0;
    unsigned char temp = 0;

    // i can not be unsigned int, otherwise i can not less than 0
    for (int i = (int)mData.size() - 1; i >= 0; i--)
    {
        if (number == 0)
        {
            break;
        }
        temp = mData[i] + (unsigned char)(number % RADIX) + carry;
        number /= RADIX;
        mData[i] = temp % RADIX;
        carry = temp / RADIX;
    }
    number += carry;
    while (number > 0)
    {
        mData.push_front(number % RADIX);
        number /= RADIX;
    }
    return *this;
}

TBigNumber& TBigNumber::operator+= (const TBigNumber& other)
{
    unsigned char carry = 0;
    unsigned char temp = 0;

    const std::deque<unsigned char>& otherData = other.mData;
    int otherIdx = (int)otherData.size() - 1;
    int idx = (int)mData.size() - 1;
    for (; otherIdx >= 0; otherIdx--)
    {
        temp = otherData[otherIdx] + carry;
        if (idx >= 0)
        {
            temp += mData[idx];
        }
        carry = temp / RADIX;
        temp %= RADIX;
        if (idx >= 0)
        {
            mData[idx] = temp;
        }
        else
        {
            mData.push_front(temp);
        }
        idx--;
    }
    while (carry > 0)
    {
        if (idx >= 0)
        {
            temp = carry + mData[idx];
            mData[idx] = temp % RADIX;
            carry = temp / RADIX;
            idx--;
        }
        else
        {
            mData.push_front(carry);
            carry = 0;
        }
    }
    return *this;
}

TBigNumber TBigNumber::operator / (unsigned int dividend)
{
    TBigNumber other = *this;
    other /= dividend;
    return other;
}

TBigNumber& TBigNumber::operator /= (unsigned int dividend)
{
    unsigned int temp = 0;
    unsigned int remainder = 0;

    for (unsigned int i = 0; i < mData.size(); i++)
    {
        temp = remainder * RADIX + mData[i];
        mData[i] = temp / dividend;
        remainder = temp % dividend;
    }
    return *this;
}

TBigNumber TBigNumber::operator * (unsigned int multiplicand)
{
    TBigNumber other = *this;
    other *= multiplicand;
    return other;
}

TBigNumber& TBigNumber::operator *= (unsigned int multiplicand)
{
#if defined(WIN32)
    // __int64 only in windows.
    unsigned __int64 temp = 0;
    unsigned __int64 carry = 0;
#else
    unsigned long long temp = 0;
    unsigned long long carry = 0;
#endif

    for (int i = (int)mData.size() - 1; i >= 0; i--)
    {
        temp = mData[i] * multiplicand + carry;
        mData[i] = temp % RADIX;
        carry = temp / RADIX;
    }
    while (carry > 0)
    {
        mData.push_front(carry % RADIX);
        carry /= RADIX;
    }
    return *this;
}

unsigned int TBigNumber::operator % (unsigned int dividend)
{
    unsigned int temp = 0;
    unsigned int remainder = 0;

    for (unsigned int i = 0; i < mData.size(); i++)
    {
        temp = remainder * RADIX + mData[i];
        remainder = temp % dividend;
    }
    return remainder;
}

bool TBigNumber::operator >= (unsigned int number)
{
    unsigned int temp = 0;
    for (unsigned int i = 0; i < mData.size(); i++)
    {
        temp = temp * RADIX + mData[i];
        if (temp >= number)
        {
            return true;
        }
    }
    return false;
}

std::string TBigNumber::ToString()
{
    unsigned int temp = 0;
    unsigned int remainder = 0;
    unsigned char cValue;
    std::string  sText;

    for (unsigned int i = 0; i < mData.size(); i++)
    {
        temp = remainder * RADIX + mData[i];
        remainder = temp % RADIX;
        if (RADIX == 16 && remainder >= 10)
        {
            // 'A' ~ 'F'
            cValue = (unsigned char)(0x41 + remainder - 10);
        }
        else
        {
            cValue = (unsigned char)(0x30 + remainder);
        }
        sText += cValue;
    }
    return sText;
}

void TBigNumber::FromString(const std::string& sText)
{
    unsigned int carry = 0;
    unsigned int temp = 0;

    mData.clear();
    for (int i = (int)sText.size() - 1; i >= 0; i--)
    {
        temp = 0;
        const char& cValue = sText[i];
        if (cValue >= 0x30 && cValue <= 0x39)           // '0' - '9'
        {
            temp = (cValue - 0x30);
        }
        else if (cValue >= 0x41 && cValue <= 0x46)      // 'A' ~ 'F'
        {
            temp = (cValue - 0x41) + 10;
        }
        else if (cValue >= 0x61 && cValue <= 0x66)      // 'a' ~ 'f'
        {
            temp = (cValue - 0x61) + 10;
        }
        temp += carry;
        mData.push_front(temp % RADIX);
        carry = temp / RADIX;
    }
    while (carry > 0)
    {
        mData.push_front(carry % RADIX);
        carry /= RADIX;
    }
}

void TBigNumber::FromPowof(unsigned int base, unsigned int exp)
{
    mData.clear();
    mData.push_front(1);

    for (unsigned int i = 0; i < exp; i++)
    {
        *this *= base;
    }
}
