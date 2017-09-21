#ifndef _TSERIALKEY_H_
#define _TSERIALKEY_H_

// 由于Go在编译本库的静态库时，出现很多编译错误，暂未找到解决办法，因此web服务端先采用动态库
// 客户端不建议使用动态库。

#ifdef _WIN32
#   ifdef LIBSERIALKEY_EXPORT
#       define LIBSERIALKEY_API __declspec(dllexport)
#   elif defined(LIBSERIALKEY_IMPORT)
#       define LIBSERIALKEY_API __declspec(dllimport)
#   else
#       define LIBSERIALKEY_API
#   endif
#elif __GNUC__ >= 4
#   define LIBSERIALKEY_API __attribute__((visibility("default")))
#else
#   define LIBSERIALKEY_API
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
    /*
    key     : [out] 生成的key
    keyLen  : [in] key的长度，长度不能小于25
    secret  : [in] 密码，比如"mpr"
    feature : [in] 特征
    days    : [in] 序列号时长（单位:天），最大不能超过999。如果为0，表示是长期
    userInfo: [in][opt] 用户信息，比如用户名或硬盘序列号。如果为空，生成的序列号随机。

    return  : 0 表示成功，其它表示失败
    remarks : 字符串参数建议使用UTF-8编码
    */
    LIBSERIALKEY_API int GenerateKey(char* key, int keyLen, const char* secret, unsigned char feature,
        int days, const char* userInfo);

    /*
    key     : [in] 验证的key
    secret  : [in] 密码，和生成相同
    feature : [in] 特征，和生成相同
    days    : [out][opt] 时长，获取到该时间后，计算系统的当前时间和安装时间差，是否超过该时间。
    userInfo: [in][opt] 验证的用户信息，和生成相同或为空。

    return  : 0 表示成功，其它表示失败
    remarks : 字符串参数编码须与生成相同
    */
    LIBSERIALKEY_API int ValidateKey(const char* key, const char* secret, unsigned char feature,
        int* days, const char* userInfo);

#ifdef __cplusplus
}
#endif

#endif // _TSERIALKEY_H_
