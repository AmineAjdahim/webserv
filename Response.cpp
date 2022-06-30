#include "Response.hpp"

Response::Response(Request *req, Server *srv):
_req(req), _srv(srv), _cgi(_req, _client)
{
    std::map<std::string, std::string> _treatments;

    
	_treatments["200"] = "OK";
	_treatments["201"] = "Created";
	_treatments["202"] = "Accepted";
	_treatments["204"] = "No Content";                  //
	_treatments["300"] = "Redirection";                 //
	_treatments["301"] = "Moved Permanently";                   //
	_treatments["302"] = "Found";                   //
	_treatments["400"] = "Bad Request";                 //
	_treatments["401"] = "Unauthorized";                    //              <--- this is for quick search instead of lots of ifs and elses
	_treatments["403"] = "Forbidden";                   //
	_treatments["404"] = "Not Found";                   //
	_treatments["405"] = "Method Not Allowed";                  //
	_treatments["408"] = "Request Timeout";                 //
	_treatments["413"] = "Payload Too Large";                   //
	_treatments["414"] = "URI Too Long";
	_treatments["500"] = "Internal Server Error";
	_treatments["501"] = "Not Implemented";
	_treatments["502"] = "Bad Gateway";
	_treatments["503"] = "Service Unavailable";
	_treatments["505"] = "HTTP Version Not Supported";


	bool		isConnectReq = _req->getMethod().value == "CONNECT";
	setHeader("Date", getFormattedTime()); // need to get time
	setHeader("Server", SERVER_NAME); // need to define constant SERVER_NAME

	try
	{
		std::map<std::string, treatment>::const_iterator		it;

		it = _treatments.find(req->getMethod().value);
		if (it == _treatments.end()) // NOT FOUND 
			throw "405";
		if (!isConnectReq)
		{
			if (req->getLoc()->root.overrided)
				_uriRooted = _req->getLoc()->root.value + "/" + _req->getUri().value.substr(_req->getLoc()->uri.size());
			else
				_uriRooted = _req->getLoc()->root.value + "/" +  _req->getUri().value;

			if (_req->getLoc()->auth.isActive() && !isAuthenticated())
			{
				setHeader("Authenticate", "Basic realm=" + _req->getLoc()->auth.realm);
					throw "401"; // Not authenticated
			}
		}
	}
	catch (const Error &error) // we need a class Error
	{
		perror(error.statusCode);
	}
}

Response::~Response()
{
}