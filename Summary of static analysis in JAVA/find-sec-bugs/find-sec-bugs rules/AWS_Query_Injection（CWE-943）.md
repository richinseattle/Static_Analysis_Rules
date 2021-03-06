###AWS Query Injection
查询注入攻击
**Bug Pattern：** AWS_QUERY_INJECTION
####描述：
构造包含用户输入的SimpleDB查询可能允许攻击者查看未经授权的记录。

以下示例动态构造并执行SimpleDB select（）查询，以允许用户指定productCategory。 攻击者可以修改查询，绕过所需的customerID身份验证并查看匹配任何客户的记录。

- [x] 安全相关

####漏洞代码：
```java
...

String customerID = getAuthenticatedCustomerID(customerName, customerCredentials);

String productCategory = request.getParameter("productCategory");

...

AmazonSimpleDBClient sdbc = new AmazonSimpleDBClient(appAWSCredentials);

String query = "select * from invoices where productCategory = '"

            + productCategory + "' and customerID = '"

            + customerID + "' order by '"

            + sortColumn + "' asc";

SelectResult sdbResult = sdbc.select(new SelectRequest(query));

```
####解决方案：
This issue is analogical to SQL Injection. Sanitize user input before using it in a SimpleDB query.
#### Check级别：AST

####相关信息：
1. [CWE-943: Improper Neutralization of Special Elements in Data Query Logic](https://cwe.mitre.org/data/definitions/943.html)


