###请求分发文件泄露
格式字符串操作

**Bug Pattern：**REQUESTDISPATCHER_FILE_DISCLOSURE
####描述：
使用用户输入构建服务器端重定向路径可能允许攻击者下载应用程序二进制文件（包括应用程序类或jar文件）或查看受保护目录中的任意文件。

攻击者可能会伪造请求参数以匹配敏感文件位置。

- [x] 安全相关

####漏洞代码：
```
String jspFile = request.getParameter("jspFile");

request.getRequestDispatcher("/WEB-INF/jsps/" + jspFile + ".jsp").include(request, response);
```
####解决方案：
Avoid constructing server-side redirects using user controlled input.

#### Check级别：AST

####相关信息：
1. [CWE-552: Files or Directories Accessible to External Parties](https://cwe.mitre.org/data/definitions/552.html)

