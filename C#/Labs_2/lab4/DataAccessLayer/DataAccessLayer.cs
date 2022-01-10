using System;
using System.Data;
using DataAccessLayer.Models;
using System.Data.SqlClient;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Converter;
using System.Transactions;

namespace DataAccessLayer
{
    public class DataAccessLayer
    {
        SqlConnection connection;

        IParser Parser;

        public DataAccessLayer(Settings.ConnectingOptions options, IParser parser)
        {
            Parser = parser;
            string connectionString = $"Data Source={options.DataSource};Database={options.Database};User={options.User};Password={options.Password};Integrated Security={options.IntegratedSecurity}";
            using (TransactionScope scope = new TransactionScope())
            {
                connection = new SqlConnection(connectionString);
                connection.Open();
                scope.Complete();
            }
        }

        public Department GetDepartment(int id)
        {
            SqlCommand command = new SqlCommand("GetDepartment", connection);
            command.CommandType = CommandType.StoredProcedure;
            command.Parameters.Add(new SqlParameter("id", id));
            using (TransactionScope scope = new TransactionScope())
            {
                List<Department> ans = Map<Department>(command.ExecuteReader(), Parser);
                scope.Complete();
                if (ans.Count == 0)
                {
                    return new Department();
                }
                else
                {
                    return ans.First();
                }
            }
        }

        public Employee GetEmployee(int id)
        {
            SqlCommand command = new SqlCommand("GetEmployee", connection);
            command.CommandType = CommandType.StoredProcedure;
            command.Parameters.Add(new SqlParameter("id", id));
            using (TransactionScope scope = new TransactionScope())
            {
                List<Employee> ans = Map<Employee>(command.ExecuteReader(), Parser);
                scope.Complete();
                if (ans.Count == 0)
                {
                    return new Employee();
                }
                else
                {
                    return ans.First();
                }
            }
        }

        public List<Employee> GetEmployees()
        {
            SqlCommand command = new SqlCommand("GetEmployees", connection);
            command.CommandType = CommandType.StoredProcedure;
            using (TransactionScope scope = new TransactionScope())
            {
                List<Employee> ans = Map<Employee>(command.ExecuteReader(), Parser);
                scope.Complete();
                return ans;
            }
        }

        public List<Employee> GetEmployeesRange(int startIndex, int count)
        {
            SqlCommand command = new SqlCommand("GetEmployeesRange", connection);
            command.CommandType = CommandType.StoredProcedure;
            command.Parameters.Add(new SqlParameter("startIndex", startIndex));
            command.Parameters.Add(new SqlParameter("count", count));

            using (TransactionScope scope = new TransactionScope())
            {
                scope.Complete();
                List<Employee> ans = Map<Employee>(command.ExecuteReader(), Parser);
                return ans;
            }
        }

        public EmployeeDepartmentHistory GetEmployeeDepartmentHistory(int id)
        {
            SqlCommand command = new SqlCommand("GetEmployeeDepartmentHistory", connection);
            command.CommandType = CommandType.StoredProcedure;
            command.Parameters.Add(new SqlParameter("id", id));
            using (TransactionScope scope = new TransactionScope())
            {
                List<EmployeeDepartmentHistory> ans = Map<EmployeeDepartmentHistory>(command.ExecuteReader(), Parser);
                scope.Complete();
                if (ans.Count == 0)
                {
                    return new EmployeeDepartmentHistory();
                }
                else
                {
                    return ans.First();
                }
            }
        }

        public EmployeePayHistory GetEmployeePayHistory(int id)
        {
            SqlCommand command = new SqlCommand("GetEmployeePayHistory", connection);
            command.CommandType = CommandType.StoredProcedure;
            command.Parameters.Add(new SqlParameter("id", id));
            using (TransactionScope scope = new TransactionScope())
            {
                List<EmployeePayHistory> ans = Map<EmployeePayHistory>(command.ExecuteReader(), Parser);
                scope.Complete();
                if (ans.Count == 0)
                {
                    return new EmployeePayHistory();
                }
                else
                {
                    return ans.First();
                }
            }
        }

        public JobCandidate GetJobCandidate(int id)
        {
            SqlCommand command = new SqlCommand("GetJobCandidate", connection);
            command.CommandType = CommandType.StoredProcedure;
            command.Parameters.Add(new SqlParameter("id", id));
            using (TransactionScope scope = new TransactionScope())
            {
                List<JobCandidate> ans = Map<JobCandidate>(command.ExecuteReader(), Parser);
                scope.Complete();
                if (ans.Count == 0)
                {
                    return new JobCandidate();
                }
                else
                {
                    return ans.First();
                }
            }
        }

        public int EmployeeMaxID()
        {
            SqlCommand command = new SqlCommand("GetEmployeeMaxID", connection);
            command.CommandType = CommandType.StoredProcedure;
            using (TransactionScope scope = new TransactionScope())
            {
                SqlDataReader reader = command.ExecuteReader();
                reader.Read();
                int ans = reader.GetInt32(0);
                reader.Close();
                scope.Complete();
                return ans;
            }
        }

        public List<HumanResourcesInfo> GetHumanResourcesByJoin()
        {
            List<HumanResourcesInfo> ans = new List<HumanResourcesInfo>();
            SqlCommand command = new SqlCommand("GetHumanRecourcesByJoin", connection);
            command.CommandType = CommandType.StoredProcedure;
            using (TransactionScope scope = new TransactionScope())
            {
                SqlDataReader reader = command.ExecuteReader();
                while (reader.Read())
                {
                    HumanResourcesInfo humanResourcesInfo = new HumanResourcesInfo();
                    Dictionary<string, object> dict = new Dictionary<string, object>();
                    for (int i = 0; i < 4; i++)
                    {
                        string name = reader.GetName(i);
                        object val = reader.GetValue(i);
                        dict.Add(name, val);
                    }
                    humanResourcesInfo.Department = Parser.Map<Department>(dict);

                    dict = new Dictionary<string, object>();
                    for (int i = 4; i < 20; i++)
                    {
                        string name = reader.GetName(i);
                        object val = reader.GetValue(i);
                        dict.Add(name, val);
                    }
                    humanResourcesInfo.Employee = Parser.Map<Employee>(dict);

                    dict = new Dictionary<string, object>();
                    for (int i = 20; i < 26; i++)
                    {
                        string name = reader.GetName(i);
                        object val = reader.GetValue(i);
                        dict.Add(name, val);
                    }
                    humanResourcesInfo.EmployeeDepartmentHistory = Parser.Map<EmployeeDepartmentHistory>(dict);

                    dict = new Dictionary<string, object>();
                    for (int i = 26; i < 31; i++)
                    {
                        string name = reader.GetName(i);
                        object val = reader.GetValue(i);
                        dict.Add(name, val);
                    }
                    humanResourcesInfo.EmployeePayHistory = Parser.Map<EmployeePayHistory>(dict);

                    dict = new Dictionary<string, object>();
                    for (int i = 31; i < 35; i++)
                    {
                        string name = reader.GetName(i);
                        object val = reader.GetValue(i);
                        dict.Add(name, val);
                    }
                    humanResourcesInfo.JobCandidate = Parser.Map<JobCandidate>(dict);

                    ans.Add(humanResourcesInfo);
                }
            }
            return ans;
        }

        List<T> Map<T>(SqlDataReader reader, IParser parser)
        {
            List<Dictionary<string, object>> parsed = Parse(reader);
            List<T> ans = new List<T>();
            foreach (Dictionary<string, object> dict in parsed)
            {
                ans.Add(parser.Map<T>(dict));
            }
            return ans;
        }

        List<Dictionary<string, object>> Parse(SqlDataReader reader)
        {
            List<Dictionary<string, object>> ans = new List<Dictionary<string, object>>();
            while (reader.Read())
            {
                Dictionary<string, object> dict = new Dictionary<string, object>();
                for (int i = 0; i < reader.FieldCount; i++)
                {
                    string name = reader.GetName(i);
                    object val = reader.GetValue(i);
                    dict.Add(name, val);
                }
                ans.Add(dict);
            }
            reader.Close();
            return ans;
        }

        public void Log(DateTime date, string message)
        {
            SqlCommand command = new SqlCommand("Log", connection);
            command.CommandType = CommandType.StoredProcedure;

            command.Parameters.Add(new SqlParameter("date", date));
            command.Parameters.Add(new SqlParameter("message", message));

            using (TransactionScope scope = new TransactionScope())
            {
                command.ExecuteNonQuery();
                scope.Complete();
            }
        }
    }
}