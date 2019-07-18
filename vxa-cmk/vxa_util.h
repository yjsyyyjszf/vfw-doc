#pragma once

#include <stdint.h>
#include <limits>
#include <time.h>

#undef max
#undef min

namespace vxa_util	{

double inline Pow10(uint8_t exponent)
{
    static double powers[] = { 1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0, 1000000.0, 10000000.0, 100000000.0, 1000000000.0, 10000000000.0};
    return powers[exponent];
}
uint8_t inline GetExponent(int64_t value)
{
    static int64_t powers[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000};
    for(unsigned int i = 0; i < sizeof(powers)/sizeof(int64_t); ++i)
    {
        if(value == powers[i])
        {
            return (uint8_t)i;
        }
    }
    return 0xFF;
}
double inline DoublePriceFromIntWithDefault(int64_t price, uint8_t exponent, int64_t priceNullValue)
{
    static double powers[] = { 1.0,
        10.0,
        100.0,
        1000.0,
        10000.0,
        100000.0,
        1000000.0,
        10000000.0,
        100000000.0,
        1000000000.0,
        10000000000.0,
        100000000000.0,
        1000000000000.0,
        10000000000000.0,
        100000000000000.0,
        1000000000000000.0};

    if( price == std::numeric_limits<int64_t>::max() || price == priceNullValue )
        return (double)priceNullValue;

    return ((double)price / powers[exponent]);
}
double inline DoublePriceFromInt(int64_t price, uint8_t exponent)
{
    static double powers[] = { 1.0,
                               10.0,
                               100.0,
                               1000.0,
                               10000.0,
                               100000.0,
                               1000000.0,
                               10000000.0,
                               100000000.0,
                               1000000000.0,
                               10000000000.0,
                               100000000000.0,
                               1000000000000.0,
                               10000000000000.0,
                               100000000000000.0,
                               1000000000000000.0};

    if( price == std::numeric_limits<int64_t>::max() )
        return (double)price;

    return ((double)price / powers[exponent]);
}

double inline GetDoubleValue(double value, int exp)
{
    static double powers[] = { 1.0,
                               10.0,
                               100.0,
                               1000.0,
                               10000.0,
                               100000.0,
                               1000000.0,
                               10000000.0,
                               100000000.0,
                               1000000000.0,
                               10000000000.0,
                               100000000000.0,
                               1000000000000.0,
                               10000000000000.0,
                               100000000000000.0,
                               1000000000000000.0};
    double multiplier = powers[exp+1];

    long v = 0;

    if(value < 0)
          v = (long)((value * multiplier) - .5);
    else
        v = (long)((value * multiplier) + .5);

    return ((double)v)/multiplier;
}

int64_t inline IntPriceFromDouble(double price, uint8_t exponent)
{
    static double powers[] = { 1.0,
                               10.0,
                               100.0,
                               1000.0,
                               10000.0,
                               100000.0,
                               1000000.0,
                               10000000.0,
                               100000000.0,
                               1000000000.0,
                               10000000000.0,
                               100000000000.0,
                               1000000000000.0,
                               10000000000000.0,
                               100000000000000.0,
                               1000000000000000.0};
    if(price == std::numeric_limits<double>::max())
    {
    	return std::numeric_limits<int64_t>::max();
    }
    if(price < 0)
    {
        return (int64_t)((price * powers[exponent])-.5);
    }
    return (int64_t)((price * powers[exponent])+.5);
}

int64_t inline IntPriceFromDoubleAddNull(double price, uint8_t exponent, int64_t oldPriceNull)
{
    static double powers[] = { 1.0,
        10.0,
        100.0,
        1000.0,
        10000.0,
        100000.0,
        1000000.0,
        10000000.0,
        100000000.0,
        1000000000.0,
        10000000000.0,
        100000000000.0,
        1000000000000.0,
        10000000000000.0,
        100000000000000.0,
        1000000000000000.0};
    if(price == std::numeric_limits<double>::max() || price == oldPriceNull)
    {
        return std::numeric_limits<int64_t>::max();
    }
    if(price < 0)
    {
        return (int64_t)((price * powers[exponent])-.5);
    }
    return (int64_t)((price * powers[exponent])+.5);
}

inline int GetDisplayFactor(double dv)
{
    static double displayFactors [] =
    {
        0.00000001,
        0.0000001,
        0.000001,
        0.00001,
        0.0001,
        0.001,
        0.01,
        0.1,
        1.0,
        10.0,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000
    };

    if(dv == 0)
        return 0;

    int ret = -8;
    for (auto& item : displayFactors)
    {
        if (dv == item)
            break;
        ++ret;
    }
    return ret;
}

inline int GetDisplayFactor(const char* value)
{
    return  GetDisplayFactor(atof(value));
}
inline double GetDisplayFactorAsDouble(int displayFactor)
{
    static double displayFactors [] =
    {
        0.00000001,
        0.0000001,
        0.000001,
        0.00001,
        0.0001,
        0.001,
        0.01,
        0.1,
        1.0,
        10.0,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000
    };

    int idx = displayFactor + 8; // 8 is the mid point of above static list (displayFactors)
    //std::assert( idx >= 0 && idx <= 16);

    if(idx >= 0 && idx <= 16)
        return displayFactors[idx];
    return 0;
}

inline void strreverse( char* begin, char* end )
{
    char tmp;
    while( end > begin )
    {
        tmp = *end;
        *end-- = *begin;
        *begin++ = tmp;
    }
}

//
// convert an unsigned integer to char buffer
//
// [in] value
// [out] str The output buffer, should be 20 chars or more.
// [in] digits in output buffer. Should be 20 or less
// returns number of chars in bufer not counting terminating zero
inline size_t ulltoa10( uint64_t value, char* str, size_t buffsize )
{
    --buffsize;

    size_t count = 0;
    char* wstr = str;
    // Conversion. Number is reversed.
    do
    {
        if( count >= buffsize )
            break;

        *wstr++ = static_cast<char>(48 + (value % 10));
        ++count;
    } while( value /= 10 );

    // Reverse string
    strreverse( str, wstr - 1 );
    return count;
}

// convert an signed integer to char buffer
//
// [in] value
// [out] str the output buffer.  Should be 20 chars or more.
// [in] digits in output buffer. Should be 20 or less
// returns number of chars in buffer not counting terminating zero
inline size_t lltoa10( int64_t value, char* str, size_t buffsize )
{
    --buffsize;

    bool isNeg = false;
    if( value < 0 )
    {
        --buffsize;
        value = 0 - value;
        isNeg = true;
    }

    size_t count = 0;
    char* wstr = str;

    // Conversion. Number is reversed.
    do
    {
        if( count >= buffsize )
            break;

        *wstr++ = static_cast<char>(48 + (value % 10));
        ++count;
    } while( value /= 10 );


    if( isNeg )
    {
        *wstr++ = '-';
        ++count;
    }
    *wstr = '\0';

    // Reverse string
    strreverse( str, wstr - 1 );

    return count;;
}

inline uint64_t atoull10( const char* s )
{
    uint8_t i;
    uint64_t val;

    for( i = 0; s[i] == ' '; ++i );	// skip the leading whitespace

    for( val = 0; s[i] >= '0' && s[i] <= '9'; ++i )
    {
        val = (10 * val) + static_cast<uint64_t>(s[i] - '0');
    }

    return val;
}


inline uint64_t atoull10( const char* s, uint32_t count, uint32_t& consumed )
{
    uint8_t i;
    uint64_t val;

    for( i = 0; i < count && s[i] == ' '; ++i );	// skip the leading whitespace

    for( val = 0; i < count && s[i] >= '0' && s[i] <= '9'; ++i )
    {
        val = (10 * val) + static_cast<uint64_t>(s[i] - '0');
    }
    consumed = i;
    return val;
}

inline uint64_t atoull10( const char* s, uint32_t maxSize )
{
    uint8_t i;

    for( i = 0; i < maxSize && s[i] == ' '; ++i ); // skip the leading whitespace

    uint64_t val = 0;
    for( ; i < maxSize && s[i] >= '0' && s[i] <= '9'; ++i )
    {
        val = (10 * val) + static_cast<uint64_t>(s[i] - '0');
    }
    return val;
}


inline int64_t atoll10( const char* s )
{
    uint8_t i;
    int8_t sign;
    int64_t val;

    for( i = 0; s[i] == ' '; ++i );	// skip the leading whitespace

    sign = ( (s[i] == '-') ? -1 : 1 );

    if( s[i] == '+' || s[i] == '-' )
    {
        ++i;
        // skip the leading sign, if any
    }

    for( val = 0; s[i] >= '0' && s[i] <= '9'; ++i )
    {
        val = (10 * val) + (s[i] - '0');
    }

    return sign * val;
}

//static const char rev_3digit_lut[] =
//                           {
//                              "000001002003004005006007008009010011012013014015016017018019020021022023024"
//                              "025026027028029030031032033034035036037038039040041042043044045046047048049"
//                              "050051052053054055056057058059060061062063064065066067068069070071072073074"
//                              "075076077078079080081082083084085086087088089090091092093094095096097098099"
//                              "100101102103104105106107108109110111112113114115116117118119120121122123124"
//                              "125126127128129130131132133134135136137138139140141142143144145146147148149"
//                              "150151152153154155156157158159160161162163164165166167168169170171172173174"
//                              "175176177178179180181182183184185186187188189190191192193194195196197198199"
//                              "200201202203204205206207208209210211212213214215216217218219220221222223224"
//                              "225226227228229230231232233234235236237238239240241242243244245246247248249"
//                              "250251252253254255256257258259260261262263264265266267268269270271272273274"
//                              "275276277278279280281282283284285286287288289290291292293294295296297298299"
//                              "300301302303304305306307308309310311312313314315316317318319320321322323324"
//                              "325326327328329330331332333334335336337338339340341342343344345346347348349"
//                              "350351352353354355356357358359360361362363364365366367368369370371372373374"
//                              "375376377378379380381382383384385386387388389390391392393394395396397398399"
//                              "400401402403404405406407408409410411412413414415416417418419420421422423424"
//                              "425426427428429430431432433434435436437438439440441442443444445446447448449"
//                              "450451452453454455456457458459460461462463464465466467468469470471472473474"
//                              "475476477478479480481482483484485486487488489490491492493494495496497498499"
//                              "500501502503504505506507508509510511512513514515516517518519520521522523524"
//                              "525526527528529530531532533534535536537538539540541542543544545546547548549"
//                              "550551552553554555556557558559560561562563564565566567568569570571572573574"
//                              "575576577578579580581582583584585586587588589590591592593594595596597598599"
//                              "600601602603604605606607608609610611612613614615616617618619620621622623624"
//                              "625626627628629630631632633634635636637638639640641642643644645646647648649"
//                              "650651652653654655656657658659660661662663664665666667668669670671672673674"
//                              "675676677678679680681682683684685686687688689690691692693694695696697698699"
//                              "700701702703704705706707708709710711712713714715716717718719720721722723724"
//                              "725726727728729730731732733734735736737738739740741742743744745746747748749"
//                              "750751752753754755756757758759760761762763764765766767768769770771772773774"
//                              "775776777778779780781782783784785786787788789790791792793794795796797798799"
//                              "800801802803804805806807808809810811812813814815816817818819820821822823824"
//                              "825826827828829830831832833834835836837838839840841842843844845846847848849"
//                              "850851852853854855856857858859860861862863864865866867868869870871872873874"
//                              "875876877878879880881882883884885886887888889890891892893894895896897898899"
//                              "900901902903904905906907908909910911912913914915916917918919920921922923924"
//                              "925926927928929930931932933934935936937938939940941942943944945946947948949"
//                              "950951952953954955956957958959960961962963964965966967968969970971972973974"
//                              "975976977978979980981982983984985986987988989990991992993994995996997998999"
//                              "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
//                           };
//
//static const char rev_2digit_lut[] =
//                           {
//                              "0001020304050607080910111213141516171819"
//                              "2021222324252627282930313233343536373839"
//                              "4041424344454647484950515253545556575859"
//                              "6061626364656667686970717273747576777879"
//                              "8081828384858687888990919293949596979899"
//                              "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
//                           };
//
//static const std::size_t radix = 10;
//static const std::size_t radix_sqr = 100;
//static const std::size_t radix_cube = 1000;
//
//inline char* strtk_ulltoa10( uint64_t value, char* buffer, uint16_t bufSize )
//{
//    char* itr = buffer + bufSize - 1;
//    *itr = 0;
//
//    if( value )
//    {
//        while( value >= radix_sqr )
//        {
//            itr -= 3;
//            uint64_t temp_v = value / radix_cube;
//            memcpy( itr, &rev_3digit_lut[3 * (value - (temp_v * radix_cube))], 3 );
//            value = temp_v;
//        }
//
//        while( value >= radix )
//        {
//            itr -= 2;
//            uint64_t temp_v = value / radix_sqr;
//            memcpy( itr, &rev_2digit_lut[2 * (value - (temp_v * radix_sqr))], 2 );
//            value = temp_v;
//        }
//
//        if (value)
//        {
//            *(--itr) = static_cast<char>('0' + value);
//        }
//    }
//    else
//    {
//        *(--itr) = '0';
//    }
//
//    return itr;
//}
//
//inline char* strtk_ulltoa10nn( uint64_t value, char* buffer, uint16_t bufSize )
//{
//    char* itr = buffer + bufSize;
//
//    if( value )
//    {
//        while( value >= radix_sqr )
//        {
//            itr -= 3;
//            uint64_t temp_v = value / radix_cube;
//            memcpy( itr, &rev_3digit_lut[3 * (value - (temp_v * radix_cube))], 3 );
//            value = temp_v;
//        }
//
//        while( value >= radix )
//        {
//            itr -= 2;
//            uint64_t temp_v = value / radix_sqr;
//            memcpy( itr, &rev_2digit_lut[2 * (value - (temp_v * radix_sqr))], 2 );
//            value = temp_v;
//        }
//
//        if (value)
//        {
//            *(--itr) = static_cast<char>('0' + value);
//        }
//    }
//    else
//    {
//        *(--itr) = '0';
//    }
//
//    return itr;
//}
//
//inline char* strtk_lltoa10( int64_t valuex, char* buffer, uint16_t size )
//{
//    char* itr = buffer + size - 1;
//    *itr = 0;
//
//    bool negative = (valuex < 0);
//    uint64_t value = static_cast<uint64_t>((negative) ? -valuex : valuex);
//    if( value )
//    {
//        while( value >= radix_sqr )
//        {
//            itr -= 3;
//            int64_t temp_v = static_cast<int64_t>(value / radix_cube);
//            memcpy( itr, &rev_3digit_lut[3 * (value - (static_cast<uint64_t>(temp_v) * radix_cube))], 3 );
//            value = static_cast<uint64_t>(temp_v);
//        }
//
//        while( value >= radix )
//        {
//            itr -= 2;
//            int64_t temp_v = static_cast<int64_t>(value / radix_sqr);
//            memcpy( itr, &rev_2digit_lut[2 * (value - (static_cast<uint64_t>(temp_v) * radix_sqr))], 2 );
//            value = static_cast<uint64_t>(temp_v);
//        }
//
//        if( value )
//        {
//            *(--itr) = static_cast<char>('0' + value);
//        }
//
//        if( negative )
//        {
//            *(--itr) = '-';
//        }
//    }
//    else
//    {
//        *(--itr) = '0';
//    }
//
//    return itr;
//}
//
// Powers of 10 from 10^0 to 10^9
static const double pow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

inline size_t dtoa( double value,int prec, char* str, size_t strLen)
{
    // if input is larger than thres_max, revert to exponential
    const double thres_max = static_cast<double>(0x7FFFFFFF);

    double diff = 0.0;
    char* wstr = str;
    int8_t neg = 0;
    int64_t whole;
    uint32_t frac;
    double tmp;

    if( prec < 0 )
    {
        prec = 0;
    }
    else if( prec > 9 )
    {
        // precision of >= 10 can lead to overflow errors
        prec = 9;
    }


    // we'll work in positive values and deal with the
    // negative sign issue later
    if( value < 0 )
    {
        neg = 1;
        value = -value;
    }

    whole = static_cast<int64_t>(value);
    tmp = (value - static_cast<double>(whole)) * pow10[ prec ];
    frac = static_cast<uint32_t>(tmp);
    diff = tmp - frac;

    if( diff > 0.5 )
    {
        ++frac;
        /* handle rollover, e.g.  case 0.99 with prec 1 is 1.0  */
        if( frac >= pow10[ prec ] )
        {
            frac = 0;
            ++whole;
        }
    }
    else if( diff == 0.5 && ((frac == 0) || (frac & 1)) )
    {
        // if halfway, round up if odd, OR
        // if last digit is 0.  That last part is strange
        ++frac;
    }

    // for very large numbers switch back to native sprintf for exponentials.
    // anyone want to write code to replace this?
    //
    // normal printf behavior is to print EVERY whole number digit
    // which can be 100s of characters overflowing your buffers == bad
    //
    if( value > thres_max )
    {
        return sprintf_s( str, strLen, "%e", neg ? -value : value );
    }

    if( prec == 0 )
    {
        diff = value - static_cast<double>(whole);
        if( diff > 0.5 )
        {
            // greater than 0.5, round up, e.g. 1.6 -> 2
            ++whole;
        }
        else if( diff == 0.5 && (whole & 1) )
        {
            // exactly 0.5 and ODD, then round up
            // 1.5 -> 2, but 2.5 -> 2
            ++whole;
        }
    }
    else
    {
        int count = prec;
        // now do fractional part, as an unsigned number
        do
        {
            --count;
            *wstr++ = static_cast<char>(48 + (frac % 10));
        } while( frac /= 10 );

        // add extra 0s
        while( count-- > 0 )
            *wstr++ = '0';

        // add decimal
        *wstr++ = '.';
    }

    // do whole part
    // Take care of sign
    // Conversion. Number is reversed.
    do
    {
        *wstr++ = static_cast<char>(48 + (whole % 10));
    } while( whole /= 10 );

    if( neg )
        *wstr++ = '-';

    *wstr = '\0';

    strreverse( str, wstr - 1 );

    return wstr - str;
}

//inline double atod( const char* s )
//{
//    int32_t i, sign;
//    double val, power;
//
//    for( i = 0; s[i] == ' '; ++i );	// skipe the leading whitespace
//
//    sign = ( (s[i] == '-') ? -1 : 1 );
//
//    if( s[i] == '+' || s[i] == '-' )
//    {
//        ++i;
//        // skip the leading sign, if any
//    }
//
//    if( s[i] == 'N' || s[i] == 'n' )
//    {
//        unsigned long nan[2] = { 0xffffffff, 0x7fffffff };
//        double* pNan = (double*)nan;
//        return *pNan;
//    }
//
//    for( val = 0.0; s[i] >= '0' && s[i] <= '9'; ++i )
//    {
//        val = (10.0 * val) + (s[i] - '0');
//    }
//
//    if( s[i] == '.' )
//    {
//        ++i;
//        /* skip the dot(.) of a floating point */
//    }
//
//    for( power = 1.0; s[i] >= '0' && s[i] <= '9'; ++i )
//    {
//        val = (10.0 * val) + (s[i] - '0');
//        power *= 10.0;
//    }
//
//    return sign * val / power;
//}
//
//inline int64_t round( double value )
//{
//    return( (int64_t)((value > 0.0) ? (value + 0.5) : (value - 0.5)) );
//}
//
//inline int wildcmp( const char* s, const char* w )
//{
//    return( *w - '*' ?
//            *s ? (*w == '?') | (*s == *w) && wildcmp( s + 1, w+1 ) : !*w :
//            (wildcmp( s, w + 1 ) || *s) && wildcmp( s + 1, w ) );
//}
//
//inline int wildicmp( const char* s, const char* w )
//{
//    return( *w - '*' ?
//            *s ? (*w == '?') | (toupper( *s ) == toupper( *w )) && wildicmp( s + 1, w + 1 ) : !*w :
//            (wildicmp( s, w + 1 ) || *s) && wildicmp( s + 1, w ) );
//}
//
//inline int64_t fastabs( int64_t val )
//{
//    #define CHARBITS 8
//
//    int64_t mask = (val >> (sizeof(int64_t) * CHARBITS - 1));
//    return (val + mask) ^ mask;
//}
//
//inline int64_t fastcondition( int64_t val1, int64_t val2, int64_t retLess, int64_t retNotLess )
//{
//    #define WORDBITS 64
//
//    return( (((val1-val2) >> (WORDBITS-1)) & (retLess ^ retNotLess)) ^ retNotLess );
//}
//
////// inline int StrCaselessCmp(const char* str1, const char* str2)
////// {
//////     std::string str1Str(str1);
//////     std::string str2Str(str2);
//////     std::transform(str1Str.begin(), str1Str.end(), str1Str.begin(), [](int c){ return (char)::toupper(c);});
//////     std::transform(str2Str.begin(), str2Str.end(), str2Str.begin(), [](int c){ return (char)::toupper(c);});
////// 
//////     return strcmp(str1Str.c_str(), str2Str.c_str());
////// }
//inline int StrCaselessCmp(const char* str1, const char* str2)
//{
//    if( str1 == str2 )
//        return 0;
//
//    if( str1 == nullptr && str2 == nullptr )
//        return 0;
//    if( str1 == nullptr && str2 != nullptr )
//        return -1;
//    if( str1 != nullptr && str2 == nullptr )
//        return  1;
//
//    int cmp = 0;
//    while (*str1 && *str2)
//    {
//        cmp = ::towlower( *str1 ) - ::towlower( *str2 );
//        if( cmp != 0 )
//            return cmp;
//        ++str1;
//        ++str2;
//    }
//    if(*str1 != 0)
//        return 1;
//    if(*str2 != 0)
//        return -1;
//    return 0;
//}
//// inline int StrnCaselessCmp(const char* str1, const char* str2, size_t len)
//// {
////     std::string str1Str(str1);
////     std::string str2Str(str2);
////     std::transform(str1Str.begin(), str1Str.end(), str1Str.begin(), [](int c){ return (char)::toupper(c);});
////     std::transform(str2Str.begin(), str2Str.end(), str2Str.begin(), [](int c){ return (char)::toupper(c);});
//// 
////     return strncmp(str1Str.c_str(), str2Str.c_str(), len);
//// }
//inline int StrnCaselessCmp(const char* str1, const char* str2, size_t cmpCnt)
//{
//    if( str1 == str2 )
//        return 0;
//
//    if( str1 == nullptr && str2 == nullptr )
//        return 0;
//    if( str1 == nullptr && str2 != nullptr )
//        return -1;
//    if( str1 != nullptr && str2 == nullptr )
//        return  1;
//
//    size_t cnt = 0;
//    int cmp = 0;
//    while (*str1 && *str2)
//    {
//        if( cnt >= cmpCnt )
//            return 0;
//
//        cmp = ::towlower( *str1 ) - ::towlower( *str2 );
//        if( cmp != 0 )
//            return cmp;
//        ++str1;
//        ++str2;
//        ++cnt;
//    }
//    if(*str1 != 0)
//        return 1;
//    if(*str2 != 0)
//        return -1;
//    return 0;
//}
//inline void StringToUpper(std::string& theString)
//{
//    std::transform(theString.begin(), theString.end(), theString.begin(), [](int c){ return (char)::toupper(c);});
//}
//inline void StringToLower(std::string& theString)
//{
//    std::transform(theString.begin(), theString.end(), theString.begin(), [](int c){ return (char)::tolower(c);});
//}
//
//
//inline bool LooksLikeSqlInjections(const char* input)
//{
//    while (*input != 0)
//    {
//        if( *input == '\'' || *input == ';' )
//            return true;
//
//        if( *input == '-' && *(input+1) == '-' )
//            return true;
//
//        if( *input == '/' && *(input+1) == '*' )
//            return true;
//
//        if( *input == '*' && *(input+1) == '\\' )
//            return true;
//
//        if( StrnCaselessCmp(input, " xp_", 4) == 0 )
//            return true;
//
//        ++input;
//    }
//    return false;
//}

inline uint32_t TradeDateToMilt(uint16_t daysSinceEpoch)
{

    __time64_t  time =  (daysSinceEpoch + 1) * (60*60*24);
    struct tm  ts;
    _localtime64_s(&ts, &time);

    int year = (ts.tm_year+1900)*10000;
    int mon  = (ts.tm_mon+1)*100;
    return year + mon + ts.tm_mday;
}

inline void Append(char*& line, const char* item, char next)
{
    while(*item != 0)
    {
        *line++ = *item++;
    }
    if( next )
        *line++ = next;
    *line = 0;
}
inline const char* timeToString(char*& timeBuf, size_t bufSize, uint64_t time, int16_t timeBias, char next)
{
    if( timeBias == std::numeric_limits<int16_t>::min() )
    {
        char* oPtr = timeBuf;

        size_t len = ulltoa10(time, timeBuf, bufSize);
        timeBuf += len;
        if(next) *timeBuf++ = next;
        *timeBuf   = 0;
        return oPtr;
    }


    (void)bufSize;
    struct tm tmm;
    time_t    uctime ;
    uint64_t  nanoFrac;

    if( timeBias == std::numeric_limits<int16_t>::max() )
    {
        uctime  = time / (1000*1000*1000);
        nanoFrac = time % (1000*1000*1000);

        localtime_s(&tmm, &uctime);
    }
    else
    {
        uint64_t  nanoBias = 60000000000  * timeBias;
        time += nanoBias;

        uctime  = time / (1000*1000*1000);
        nanoFrac = time % (1000*1000*1000);

        gmtime_s(&tmm, &uctime);
    }

    const char* origPtr = timeBuf;

    int hour  = tmm.tm_hour;
    int min   = tmm.tm_min;
    int sec   = tmm.tm_sec;

    if( hour > 9 )
    {
        _itoa_s(hour, timeBuf, 3, 10);
        timeBuf += 2;
    }
    else
    {
        *timeBuf++ = '0';
        _itoa_s(hour, timeBuf++, 2, 10);
    }
    *timeBuf++ = ':';

    if( min > 9 )
    {
        _itoa_s(min, timeBuf, 3, 10);
        timeBuf += 2;
    }
    else
    {
        *timeBuf++ = '0';
        _itoa_s(min, timeBuf++, 2, 10);
    }
    *timeBuf++ = ':';

    if( sec > 9 )
    {
        _itoa_s(sec, timeBuf, 3, 10);
        timeBuf += 2;
    }
    else
    {
        *timeBuf++ = '0';
        _itoa_s(sec, timeBuf++, 2, 10);
    }
    *timeBuf++ = '.';

    char nanoBuf[128];
    _i64toa_s(nanoFrac, nanoBuf, sizeof(nanoBuf), 10);
    nanoBuf[10] = 0;

    int nanoLen = (int)strlen(nanoBuf) - 1;

    timeBuf += 10;

    *timeBuf--   = 0;
    *timeBuf--   = next;

    char*  nanoPtr = nanoBuf+nanoLen;
    for (int i = nanoLen; i >= 0; --i, --timeBuf, --nanoPtr)
    {
        *timeBuf = *nanoPtr;
    }
    int nanoLeft = 8 - nanoLen;
    for (size_t i = 0; i < nanoLeft; ++i, --timeBuf)
    {
        *timeBuf = '0';
    }
    // reset timebuff
    timeBuf += 11;
    return origPtr;
}

inline void Append(char*& strInt, size_t buffSize, int64_t value, char next)
{
    if( value == std::numeric_limits<int64_t>::max() )
    {
        Append(strInt, "9223372036854775807", next );
        //if(next) *strInt++ = next;
        //*strInt   = 0;
        return;
    }
    size_t len = lltoa10(value, strInt, buffSize);
    strInt += len;
    if(next) *strInt++ = next;
    *strInt   = 0;
}
inline void Append(char*& strInt, size_t buffSize, uint64_t value, char next)
{
    if( value == std::numeric_limits<uint64_t>::max() )
    {
        Append(strInt, "18446744073709551615", next );
        //if(next) *strInt++ = next;
        //*strInt   = 0;
        return;
    }

    size_t len = ulltoa10(value, strInt, buffSize);
    strInt += len;
    if(next) *strInt++ = next;
    *strInt   = 0;
}
inline void Append(char*& strInt, size_t buffSize, int32_t value, char next)
{
    if( value == std::numeric_limits<int32_t>::max() )
    {
        Append(strInt, "2147483647", next );
        //if(next) *strInt++ = next;
        //*strInt   = 0;
        return;
    }

    size_t len = lltoa10(value, strInt, buffSize);
    strInt += len;
    if(next) *strInt++ = next;
    *strInt   = 0;
}
inline void Append(char*& strInt, size_t buffSize, uint32_t value, char next)
{
    if( value == std::numeric_limits<uint32_t>::max() )
    {
        Append(strInt, "4294967295", next );
        //if(next) *strInt++ = next;
        //*strInt   = 0;
        return;
    }

    size_t len = ulltoa10(value, strInt, buffSize);
    strInt += len;
    if(next) *strInt++ = next;
    *strInt   = 0;
}
inline void doubleToString(char*& strInt, size_t buffSize, int64_t price, uint8_t exponent, char next)
{
    if( price == vxa_feed::PRICE_NULL_64 )
    {
        Append(strInt, "9223372036854775807.000000", next );
        //if(next) *strInt++ = next;
        //*strInt   = 0;
        return;
    }

    double prc = DoublePriceFromIntWithDefault( price, exponent, 0x7FFFFFFFFFFFFFFF );

                // size_t len = sprintf_s(strInt, buffSize, "%0.6f", prc);
    size_t len = dtoa( prc,6, strInt, buffSize);

    strInt += len;
    if(next)
        *strInt++ = next;
    *strInt   = 0;
    return;
}

// string creation methods
//
inline const char* bitmapAsString(char* bitString, size_t size, uint8_t bm)
{
    char* ptr = bitString + (size-1);

    *ptr-- = 0;
    *ptr-- = '\'';
    for (int bit = 0; bit<8; bit++)
    {
        *ptr-- = (((bm >> bit) & 0x01) == 1) ? '1' : '0';
    }
    *ptr = '\'';
    return(ptr);
}

static const char hexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

inline const char* optRectAsByteArray(char* outBuffer, const vxa_feed::VxaEvent& rec)
{
    char* ptr = outBuffer;
    const unsigned char* oRec = (const unsigned char*) &rec;

    for (int bit = 0; bit < sizeof(const vxa_feed::VxaEvent); ++bit)
    {
        *ptr++ = hexChars[(oRec[bit] & 0xF0) >> 4];
        *ptr++ = hexChars[oRec[bit] & 0x0F];
        *ptr++ = ' ';
    }
    *ptr++ = '\n';
    *ptr = 0;
    return(outBuffer);
}

inline const char* ToString( vxa_feed::BookAction type )
{
    switch (type)
    {
    case vxa_feed::BookAction::NotSet     : return "U";
    case vxa_feed::BookAction::New        : return "N";
    case vxa_feed::BookAction::Change     : return "C";
    case vxa_feed::BookAction::Delete     : return "D";
    case vxa_feed::BookAction::DeleteThru : return "DT";
    case vxa_feed::BookAction::DeleteFrom : return "DF";
    case vxa_feed::BookAction::Overlay    : return "O";
    case vxa_feed::BookAction::Replace    : return "R";
    }
    __declspec(thread) static char szTemp[16];
    sprintf_s(szTemp, sizeof(szTemp), "UNK=%d", type);
    return(szTemp);
}
inline const char*  ToString(vxa_feed::AggressorSide value)
{
    switch (value)
    {
    case vxa_feed::AggressorSide::Buy         : return "BA";
    case vxa_feed::AggressorSide::Sell        : return "SA";
    }
    return "NA" ;
}
inline const char*  ToString(vxa_feed::HaltReason value)
{
    switch (value)
    {
        case vxa_feed::HaltReason::GroupSchedule           : return "GroupSchedule";
        case vxa_feed::HaltReason::SurveillanceIntervention: return "SurveillanceIntervention";
        case vxa_feed::HaltReason::MarketEvent             : return "MarketEvent";
        case vxa_feed::HaltReason::InstrumentActivation    : return "InstrumentActivation";
        case vxa_feed::HaltReason::InstrumentExpiration    : return "InstrumentExpiration";
        case vxa_feed::HaltReason::Unknown                 : return "Unknown";
        case vxa_feed::HaltReason::RecoveryInProcess       : return "RecoveryInProcess";
    }
    return "None";
}
inline const char*  ToString(vxa_feed::SecurityTradingStatus value)
{
    switch (value)
    {
    case vxa_feed::SecurityTradingStatus::TradingHalt            : return "TradingHalt";
    case vxa_feed::SecurityTradingStatus::Close                  : return "Close";
    case vxa_feed::SecurityTradingStatus::NewPriceIndication     : return "NewPriceIndication";
    case vxa_feed::SecurityTradingStatus::ReadyToTrade           : return "ReadyToTrade";
    case vxa_feed::SecurityTradingStatus::NotAvailableForTrading : return "NotAvailableForTrading";
    case vxa_feed::SecurityTradingStatus::UnknownorInvalid       : return "UnknownorInvalid";
    case vxa_feed::SecurityTradingStatus::PreOpen                : return "PreOpen";
    case vxa_feed::SecurityTradingStatus::PreCross               : return "PreCross";
    case vxa_feed::SecurityTradingStatus::Cross                  : return "Cross";
    case vxa_feed::SecurityTradingStatus::PostClose              : return "PostClose";
    case vxa_feed::SecurityTradingStatus::PreClose               : return "PreClose";
    case vxa_feed::SecurityTradingStatus::NoChange               : return "NoChange";

    case vxa_feed::SecurityTradingStatus::Restricted             : return "Restricted";
    case vxa_feed::SecurityTradingStatus::Freeze                 : return "Freeze";
    }
    return "None";
}
inline const char*  ToString(vxa_feed::BookType value)
{
    switch (value)
    {
    case vxa_feed::BookType::Bid         : return "B";
    case vxa_feed::BookType::Offer       : return "S";
    case vxa_feed::BookType::ImpliedBid  : return "iB";
    case vxa_feed::BookType::ImpliedOffer: return "iS";
    case vxa_feed::BookType::BookReset   : return "R";
    }
    return "U";
}
inline const char*  ToString(vxa_feed::StatisticsType value)
{
    switch (value)
    {
    case vxa_feed::StatisticsType::OpenPrice  : return "OpenPrice";
    case vxa_feed::StatisticsType::HighTrade  : return "HighTrade";
    case vxa_feed::StatisticsType::LowTrade   : return "LowTrade";
    case vxa_feed::StatisticsType::HighestBid : return "HighBid";
    case vxa_feed::StatisticsType::LowestOffer: return "LowOffer";
    }
    return "NotSet";
}

inline const char*  ToString(vxa_feed::DailyStatisticsType value)
{
    switch (value)
    {
    case vxa_feed::DailyStatisticsType:: SettlementPrice: return "SettlementPrice";
    case vxa_feed::DailyStatisticsType:: ClearedVolume  : return "ClearedVolume";
    case vxa_feed::DailyStatisticsType:: OpenInterest   : return "OpenInterest";
    case vxa_feed::DailyStatisticsType:: FixingPrice    : return "FixingPrice";
    }
    return "NotSet";
}

inline const char*  ToString(vxa_feed::OpenCloseSettlFlag value)
{
    switch (value)
    {
    case vxa_feed::OpenCloseSettlFlag::DailyOpenPrice         : return "DailyOpenPrice";
    case vxa_feed::OpenCloseSettlFlag::IndicativeOpeningPrice : return "IndicativeOpeningPrice";
    }
    return "Unk";
}

inline const char*  ToString(vxa_feed::SecurityTradingEvent value)
{
    switch (value)
    {
    case vxa_feed::SecurityTradingEvent::NoCancel          : return "NoCancel";
    case vxa_feed::SecurityTradingEvent::ResetStatistics   : return "ResetStatistics";
    case vxa_feed::SecurityTradingEvent::ImpliedMatchingON : return "ImpliedMatchingON";
    case vxa_feed::SecurityTradingEvent::ImpliedMatchingOFF: return "ImpliedMatchingOFF";
    }
    return "";
}
inline size_t VxaEventAsString(char* outBuffer, size_t bufferSize, const vxa_feed::VxaEvent& rec, uint8_t exponent, int16_t timeBias)
{
        // TODO: Deal correctly with buffer size
    if( bufferSize < 255 )
    {
        *outBuffer = 0;
        return 0;
    }

    const char real = rec.realEvent ? 'R':'G';
    char* origPtr   = outBuffer;

    switch (rec.unionId)
    {
    case vxa_feed::UnionId::TransactionMarker:
        if( rec.transactionMarker.type == vxa_feed::TransactionType::TransactionStart )
        {
            Append(outBuffer, "TS,R", ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            Append(outBuffer, "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvTS", '\n');
        }
        else
        {
            Append(outBuffer, "TE,R", ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            Append(outBuffer, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^TE", '\n');
        }
        return (outBuffer - origPtr);

    case vxa_feed::UnionId::ChannelReset:

        Append(outBuffer, "CR,R", ',');

        timeToString(outBuffer, 128, rec.time, timeBias, ',');
        Append(outBuffer, 128, rec.gseq, ',');
        Append(outBuffer, 128, rec.instrumentId, ',');
        Append(outBuffer, "channel reset", '\n');
        return (outBuffer - origPtr);

    case vxa_feed::UnionId::BookLevel:
    {
        Append(outBuffer, "LD,R", ',');

        timeToString(outBuffer, 128, rec.time, timeBias, ',');
        Append(outBuffer, 128, rec.gseq, ',');
        Append(outBuffer, 128, rec.seq, ',');
        Append(outBuffer, 128, rec.instrumentId, ',');
        Append(outBuffer, rec.IsEndOfEvent() ? "EOE" : ToString(rec.bookEntry.bookType), ',');
        Append(outBuffer, ToString(rec.bookEntry.action), ',');
        Append(outBuffer, 128, (int)rec.bookEntry.priceLevel, ',');

        doubleToString(outBuffer, 128, rec.bookEntry.price, exponent, ',');
        Append(outBuffer, 128,  rec.bookEntry.aggQty, ',');
        Append(outBuffer, 128, rec.bookEntry.numberOfOrders ==  vxa_feed::PRICE_NULL ? 0 : rec.bookEntry.numberOfOrders, ',');
        Append(outBuffer, 128, rec.bookEntry.impliedsAggQty, ',');
        Append(outBuffer, 128,rec.bookEntry.impliedNumberOfOrders ==  vxa_feed::PRICE_NULL ? 0 : rec.bookEntry.impliedNumberOfOrders, '\n');
        return (outBuffer - origPtr);
    }
    case vxa_feed::UnionId::DetailedOrderBook:
        {
            uint64_t prevOrderId = rec.orderBookEntry.prevOrderId;

            if (rec.orderBookEntry.action != vxa_feed::BookAction::Replace)
            {
                prevOrderId = 0;
            }

            Append(outBuffer, "OD,", real);
            *outBuffer++ = ',';

            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            Append(outBuffer, ToString(rec.orderBookEntry.bookType), ',');
            Append(outBuffer, ToString(rec.orderBookEntry.action), ',');

            doubleToString(outBuffer, 128, rec.orderBookEntry.price, exponent, ',');
            Append(outBuffer, 128, rec.orderBookEntry.displayQuantity, ',');
            Append(outBuffer, 128, rec.orderBookEntry.priority, ',');

            if( prevOrderId != 0 )
            {
                Append(outBuffer, 128, rec.orderBookEntry.origOrderId, ',');
                Append(outBuffer, 128, rec.orderBookEntry.orderID, ',');
                Append(outBuffer, 128, rec.orderBookEntry.prevOrderId, '\n');
                return (outBuffer - origPtr);
            }
            else if(prevOrderId == 0 && rec.orderBookEntry.origOrderId != 0) 
            {
                Append(outBuffer, 128, rec.orderBookEntry.origOrderId, ',');
                Append(outBuffer, 128,rec.orderBookEntry.orderID, '\n');
                return (outBuffer - origPtr);
            } 
           // std::assert( prevOrderId == 0 && rec.orderBookEntry.origOrderId == 0 );

            Append(outBuffer, 128,rec.orderBookEntry.orderID, '\n');
            return (outBuffer - origPtr);
        }

    case vxa_feed::UnionId::TradeSummary:
        {
                Append(outBuffer, "TR,", real);
                *outBuffer++ = ',';

                timeToString(outBuffer, 128, rec.time, timeBias, ',');
                Append(outBuffer, 128, rec.gseq, ',');
                Append(outBuffer, 128, rec.seq, ',');
                Append(outBuffer, 128, rec.instrumentId, ',');
                Append(outBuffer, ToString(rec.tradeSummary.aggressorSide), ',');

                doubleToString(outBuffer, 128, rec.tradeSummary.price, exponent, ',');

                Append(outBuffer, 128, rec.tradeSummary.tradeQuantity, ',');
                Append(outBuffer, 128, rec.tradeSummary.numberOfMatches, ',');

                if( rec.tradeSummary.isImplieds  )
                    *outBuffer++ = 'I';
                *outBuffer++= '\n';
                *outBuffer  = 0;

            return (outBuffer - origPtr);
        }

    case vxa_feed::UnionId::TradeMatch:
        {
            char bitMask[20];

            Append(outBuffer, "Tm,", real);
            *outBuffer++ = ',';

            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            Append(outBuffer, rec.matchEntry.isAggressor ? "Aggr":"", ',');
            Append(outBuffer, 128, rec.matchEntry.matchNumber + 1, ',');
            Append(outBuffer, 128, (uint64_t)rec.matchEntry.orderId, ',');
            Append(outBuffer, 128, rec.matchEntry.tradeQuantity, ',');
            Append(outBuffer, bitmapAsString(bitMask, sizeof(bitMask), (uint8_t)rec.matchEntry.flags), '\n');

            return (outBuffer - origPtr);
        }

    case vxa_feed::UnionId::VolumeUpdate:
        {
            Append(outBuffer, "VU,", real);
            *outBuffer++ = ',';

            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            Append(outBuffer, 128, rec.volumeEntry.marketVolume, '\n');
            return (outBuffer - origPtr);;
        }

    case vxa_feed::UnionId::SessionStatistics:

            Append(outBuffer, "SE,", real);
            *outBuffer++ = ',';

            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');

            Append(outBuffer, ToString(rec.sessionStatsEntry.statType),           ',');
            Append(outBuffer, ToString(rec.sessionStatsEntry.openCloseSettlFlag), ',');
            doubleToString(outBuffer, 128, rec.sessionStatsEntry.price,   exponent, ',');
            Append(outBuffer, 128, rec.sessionStatsEntry.size, '\n');
            return (outBuffer - origPtr);

    case vxa_feed::UnionId::LimitsBanding:

            Append(outBuffer, "LM,", real);
            *outBuffer++ = ',';

            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            doubleToString(outBuffer, 128, rec.bandingEntry.lowLimitPrice,     exponent, ',');
            doubleToString(outBuffer, 128, rec.bandingEntry.highLimitPrice,    exponent, ',');
            doubleToString(outBuffer, 128, rec.bandingEntry.maxPriceVariation, exponent, '\n');
            return (outBuffer - origPtr);

    case vxa_feed::UnionId::DailyStatistics:
        {
            char bank4Buffer[80];

            Append(outBuffer, "ST,", real);
            *outBuffer++ = ',';

            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            Append(outBuffer, ToString(rec.dailyStatsEntry.dailyStatsType), ',');
            Append(outBuffer, bitmapAsString(bank4Buffer, sizeof(bank4Buffer), (uint8_t)rec.dailyStatsEntry.settlPriceType), ',');

            doubleToString(outBuffer, 128, rec.dailyStatsEntry.price, exponent, ',');
            Append(   outBuffer, 128, rec.dailyStatsEntry.size == std::numeric_limits<int32_t>::max() ? 0 : rec.dailyStatsEntry.size, ',');
            Append(  outBuffer, 128, TradeDateToMilt(rec.dailyStatsEntry.tradingReferenceDate), '\n');
            return (outBuffer - origPtr);
        }

    case vxa_feed::UnionId::SecurityStatus:

            Append(outBuffer, "SS,R", ',');
            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');

            Append(outBuffer, ToString(rec.securityStatus.securityTradingStatus), ',');
            Append(outBuffer, ToString(rec.securityStatus.haltReason),            ',');
            Append(outBuffer, ToString(rec.securityStatus.securityTradingEvent),   ',');

            Append(outBuffer, 128, TradeDateToMilt(rec.securityStatus.tradeDate), ',');

            Append(outBuffer, rec.securityStatus.securityGroup, ',');
            Append(outBuffer, rec.securityStatus.asset,         '\n');
            return (outBuffer - origPtr);

    case vxa_feed::UnionId::AuctionClearingPrice:

            Append(outBuffer, "AC,R", ',');
            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            doubleToString(outBuffer, 128,rec.clearingPrice.price, exponent, ',');
            Append(outBuffer, 128, rec.clearingPrice.quantity, '\n');
            return (outBuffer - origPtr);

    case vxa_feed::UnionId::InvestigatedTrade:

            Append(outBuffer, "IT,R", ',');
            timeToString(outBuffer, 128, rec.time, timeBias, ',');
            Append(outBuffer, 128, rec.gseq, ',');
            Append(outBuffer, 128, rec.seq, ',');
            Append(outBuffer, 128, rec.instrumentId, ',');
            doubleToString(outBuffer, 128,rec.investigatedTrade.price, exponent, ',');
            Append(outBuffer, 128, rec.investigatedTrade.quantity, ',');
            *outBuffer++ = (rec.investigatedTrade.status == vxa_feed::InvestigateStatus::UnderInvestigation ? 'U':'C');
            *outBuffer++ = '\n';
            *outBuffer   = 0;
            return (outBuffer - origPtr);
    }

    // Default case
    Append(outBuffer, "UK,U", ',');
    timeToString(outBuffer, 128, rec.time, timeBias, ',');
    Append(outBuffer, 128, rec.gseq, ',');
    Append(outBuffer, 128, rec.seq, ',');
    Append(outBuffer, 128, rec.instrumentId, ',');
    Append( outBuffer, 128, (int)rec.unionId, '\n');
    return (outBuffer - origPtr);
}

inline const char* ReverseBitmapAsString(char* bitString, uint8_t bm)
{
    char* ptr = bitString;
    *ptr++ = '\'';
    for (int bit = 0; bit<8; bit++)
    {
        *ptr++ = (((bm >> bit) & 0x01) == 1) ? '1' : '0';
    }
    *ptr++ = '\'';
    *ptr = 0;
    return(bitString);
}
inline size_t VxaEventLegacySSAsString(char* outBuffer, size_t bufferSize, const vxa_feed::VxaEvent& rec)
{
        // TODO: Deal correctly with buffer size
    if( bufferSize < 255 )
    {
        *outBuffer = 0;
        return 0;
    }

    char* origPtr = outBuffer;
    char bank2Buffer[32];

    Append(outBuffer, "SS", ',');
    timeToString(outBuffer, 128, rec.time, std::numeric_limits<int16_t>::max(), ',');
    Append(outBuffer, 128, rec.gseq, ',');
    Append(outBuffer, ReverseBitmapAsString(bank2Buffer, (uint8_t)rec.eventIndicator), ',');
    Append(outBuffer, 128, (int)rec.securityStatus.securityTradingStatus, ',');
    Append(outBuffer, 128, (int)rec.securityStatus.haltReason, ',');
    Append(outBuffer, 128, (int)rec.securityStatus.securityTradingEvent, ',');
    Append(outBuffer, 128, TradeDateToMilt(rec.securityStatus.tradeDate), ',');
    Append(outBuffer, 128, rec.instrumentId, ',');
    Append(outBuffer, rec.securityStatus.securityGroup[0] == 0 ? "" : rec.securityStatus.securityGroup, ',');
    Append(outBuffer, rec.securityStatus.asset[0] == 0         ? "" : rec.securityStatus.asset, '\n');
    return (outBuffer - origPtr);
}

//-----------------------------------------------------------------------------------------------------------=
}	//namespace vxa_feed  {
//-----------------------------------------------------------------------------------------------------------=
