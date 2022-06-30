#ifndef RESPONSE_HPP
# define RESPONSE_HPP

//#include "request.hpp"
//# include "../CGI/CGI.hpp"
// we need an Error class that will handle errors

class Response {
public:
	Response(Request *req, Server *srv);
	~Response();

	void			getFun(void);
	void			postFun(void);

private:
    Request *_req;
	Server  *_srv;
    std::string _uriRooted;
    static const std::map<std::string, treatment>   _treatments;
    CGI _cgi;
	
};




#endif