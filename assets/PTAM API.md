# Program Temporary Access Memory (PTAM)

### PTAM member functions 

* storeString(): 
* storeDouble():
* storeInt():
* getStringData():
* getDoubleData(): 
* getIntData():
* clearData():
* clearAllData():
* getLastString():
* getLastDouble():
* getLastInt():

### Function Documentation

            void storeString(const std::string& id, const std::string& data)

<b> Returns: </b>
    None

<b> Parameters:</b>

* Designated ID - This creates the PTAM register with this ID an can only be referenced with this ID string
* Data Value <std::string> - Data value of type <std::string>


---------------------------------------------------------

            void storeDouble(const std::string& id, double data)

<b> Returns: </b>
    None

<b> Parameters: </b>

* Designated ID - This creates the PTAM register with this ID an can only be referenced with this ID string
* Data Value <double> - Data value of type <double>

---------------------------------------------------------

            void storeInt(const std::string& id, int data)

<b> Returns: </b>
    None

<b> Parameters: </b>

* Designated ID - This creates the PTAM register with this ID an can only be referenced with this ID string
* Data Value <int> - Data value of type <int>

---------------------------------------------------------

            std::vector<std::string> getStringData(const std::string& id)

<b> Returns: </b>
    std::vector<std::string>
    Function returns a vector of all the values stored in the specific PTAM register since program boot

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

--------------------------------------------------------

            std::vector<double> getDoubleData(const std::string& id)

<b> Returns: </b>
    std::vector<double>
    Function returns a vector of all the values stored in the specific PTAM register since program boot

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            std::vector<int> getIntData(const std::string& id)

<b> Returns: </b>
    std::vector<int>
    Function returns a vector of all the values stored in the specific PTAM register since program boot

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            void clearData(const std::string& id)

Function clears all data stored in a vector from a specific PTAM register

<b> Returns: </b>
    None

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            void clearAllData()

Function clears all data in all PTAM reggisters (!! Danger Zone !!)

<b> Returns: </b>
    None

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            std::string getLastString(const std::string& id)

<b> Returns: </b>
    std::string
    Function returns the most recent value stored in the PTAM register of type<std::string>. 

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

--------------------------------------------------------

            double getLastDouble(const std::string& id)

<b> Returns: </b>
    double
    Function returns the most recent value stored in the PTAM register of type<double>.

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            int getLastInt(const std::string& id)

<b> Returns: </b>
    double
    Function returns the most recent value stored in the PTAM register of type<int>.

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------