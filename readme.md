# Part-time Wage Estimation for MVL

Calculates each person’s total wage for the month, with estimated extra insurance paid by the employer.

## Environment
- **OS**: Windows 11  
- **Compiler**: Visual Studio 2022  
- **Extra Dependency**:  
  - [rapidjson](https://github.com/Tencent/rapidjson.git)  

> Should also work on Linux with GCC.

## Execution in CLI
Main file: `main.cpp`  
### Steps:  
1. Compile `main.cpp` with your compiler.  
    - e.g. ```.\cmpmain.ps1``` 
      - for win11 with VC and PowerShell 
2. Run the resulting executable.  
   - Arguments:  
       1. Path to this month’s insurance log for each person.  

### Example:  
For win11 with PowerShell
```
.\out.exe .\insure_log\2025_07_m2.json
```
## TODO
- GUI
  - A web-based form would be preferable.
  - Provide interactive features for easier and more convenient estimation.
