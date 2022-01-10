using System;
using Converter;
using Logger;
using DataAccessLayer;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ServiceLayer
{
    public class ServiceLayer
    {
        public DataAccessLayer.DataAccessLayer DAL;
        IParser Parser;
        ILogger Logger;
        public ServiceLayer(DataAccessLayer.Settings.ConnectingOptions options, IParser parser, ILogger logger)
        {
            DAL = new DataAccessLayer.DataAccessLayer(options, parser);
            Parser = parser;
            Logger = logger;
        }

        public DataAccessLayer.Models.HumanResourcesInfo GetPersonInfo(int id)
        {
            DataAccessLayer.Models.Employee employee = DAL.GetEmployee(id);
            DataAccessLayer.Models.HumanResourcesInfo personInfo = LoadEmployee(employee);

            return personInfo;
        }

        public List<DataAccessLayer.Models.HumanResourcesInfo> GetEmployees()
        {
            List<DataAccessLayer.Models.Employee> employees = DAL.GetEmployees();
            List<DataAccessLayer.Models.HumanResourcesInfo> ans = new List<DataAccessLayer.Models.HumanResourcesInfo>();
            foreach (DataAccessLayer.Models.Employee employee in employees)
            {
                DataAccessLayer.Models.HumanResourcesInfo humanResourcesInfo = LoadEmployee(employee);
                ans.Add(humanResourcesInfo);
            }

            return ans;
        }

        public List<DataAccessLayer.Models.HumanResourcesInfo> GetPersonsRange(int startIndex, int finishIndex)
        {
            List<DataAccessLayer.Models.Employee> employees = DAL.GetEmployeesRange(startIndex, finishIndex);
            List<DataAccessLayer.Models.HumanResourcesInfo> ans = new List<DataAccessLayer.Models.HumanResourcesInfo>();
            foreach (DataAccessLayer.Models.Employee employee in employees)
            {
                DataAccessLayer.Models.HumanResourcesInfo personInfo = LoadEmployee(employee);
                ans.Add(personInfo);
            }

            return ans;
        }

        public List<DataAccessLayer.Models.HumanResourcesInfo> GetHumanResourcesByJoin()
        {
            return DAL.GetHumanResourcesByJoin();
        }

        DataAccessLayer.Models.HumanResourcesInfo LoadEmployee(DataAccessLayer.Models.Employee employee)
        {
            int id = employee.BusinessEntityID;
            DataAccessLayer.Models.EmployeeDepartmentHistory employeeDepartmentHistory = DAL.GetEmployeeDepartmentHistory(id);
            DataAccessLayer.Models.Department department = DAL.GetDepartment(employeeDepartmentHistory.DepartmentID);
            DataAccessLayer.Models.EmployeePayHistory employeePayHistory = DAL.GetEmployeePayHistory(id);
            DataAccessLayer.Models.JobCandidate jobCandidate = DAL.GetJobCandidate(id);
            DataAccessLayer.Models.HumanResourcesInfo humanResourcesInfo = new DataAccessLayer.Models.HumanResourcesInfo(department, employee, employeeDepartmentHistory, employeePayHistory, jobCandidate);
            return humanResourcesInfo;
        }
    }
}