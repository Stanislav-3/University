using System;
using System.Collections.Generic;
using System.Text;

namespace DataAccessLayer.Models
{
    public class HumanResourcesInfo
    {
        public Department Department { get; set; }
        public Employee Employee { get; set; }
        public EmployeeDepartmentHistory EmployeeDepartmentHistory { get; set; }
        public EmployeePayHistory EmployeePayHistory { get; set; }
        public JobCandidate JobCandidate { get; set; }

        public HumanResourcesInfo(Department department, Employee employee, EmployeeDepartmentHistory employeeDepartmentHistory,
            EmployeePayHistory employeePayHistory, JobCandidate jobCandidate)
        {
            Department = department;
            Employee = employee;
            EmployeeDepartmentHistory = employeeDepartmentHistory;
            EmployeePayHistory = employeePayHistory;
            JobCandidate = jobCandidate;
        }

        public HumanResourcesInfo() 
        { 

        }

    }
}
