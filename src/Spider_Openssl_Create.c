#include <Spider.h>

ssl_t * Spider_Openssl_Create(int webfd)
{
	ssl_t * ssl=(ssl_t *)calloc(1,sizeof(ssl_t));
	/*初始加载错误信息*/
	SSL_load_error_strings();
	/*初始化openssl库*/
	SSL_library_init();
	/*添加SSL,加密功能及散列函数*/
	OpenSSL_add_all_algorithms();
	/*生成兼容2.0或者3.0的环境信息*/
	ssl->ctx = SSL_CTX_new(SSLv23_method());
	/*生成安全通信句柄*/
	ssl->socket = SSL_new(ssl->ctx);
	/*使用原有的通信socket与ssl相关联*/
	SSL_set_fd(ssl->socket,webfd);
	SSL_connect(ssl->socket);
	printf("[3] SSL Connect WebServer Success..\n");
	return ssl;
}
