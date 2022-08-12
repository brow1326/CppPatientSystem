// FinalProject.cpp : Defines the entry point for the application.
//

#include "FinalProject.h"




class CovidTest {
public:
    bool result;
    long date;

    CovidTest() {
        time_t now;
        result = (rand() % 100) < 5;
        date = time(&now);
    }


};





class Patient {
public:
    std::string name;
    std::string age;
    std::string postalCode;

    std::vector<CovidTest> allTests;


    Patient(std::string n, std::string a, std::string p) {
        name = n;
        age = a;
        postalCode = p;
    }

    void performTest() {
        CovidTest test;
        allTests.push_back(test);
    }




};













int main()
{
    using namespace nana;

    std::vector<Patient> allPatients;

    form fm(API::make_center(600, 600));                        //main window
    form* formCalcStats = NULL;                                //calculate stats window
    form* formHotspots = NULL;                                 //calculate hotspots window


    //main menu labels
    label labName{ fm, "\n\n\n\n\t\t\t  Full Name " };               labName.format(true);               labName.bgcolor(color(218, 229, 235));
    label labDateOfBirth{ fm, "\n\n\n\n\t\t\t\t\tAge " };            labDateOfBirth.format(true);        labDateOfBirth.bgcolor(color(204, 221, 230));
    label labPostalCode{ fm, "\n\n\n\n\t\t\tPostal Code " };         labPostalCode.format(true);         labPostalCode.bgcolor(color(195, 211, 219));
    label labTestResult{ fm };                                       labTestResult.format(true);
    //calc stats label
    label* labCalcStats{};
    //calc hotspots label
    label* labHotspots{};


    button btnEnterPatient{ fm, "Enter patient" };
    button btnRunTest{ fm, "Run Test" };
    button btnCalculateStats{ fm, "Calculate statistics" };
    button btnHotspots{ fm, "Calculate hotspots" };
    button btnExit{ fm, "Quit" };


    textbox nameBox{ fm };
    nameBox.events().dbl_click([&] { nameBox.select(true); });
    textbox ageBox{ fm };
    ageBox.events().dbl_click([&] { ageBox.select(true); });
    textbox postalBox{ fm };
    postalBox.events().dbl_click([&] { postalBox.select(true); });


    std::string strTestResult = "a";
    //end variables








    //defining our buttons

    btnExit.events().click([&fm] {
        std::quick_exit(EXIT_SUCCESS);
        fm.close();
        });




    //////////




    Patient* selectedPatient = NULL;
    combox patientList{ fm };
    patientList.events().selected([&] {
        int selectedItem = patientList.option();
        selectedPatient = &allPatients.at(selectedItem);

        //record a covid result
        btnRunTest.events().click([&] {

            if (selectedPatient != NULL) {
                selectedPatient->performTest();


                if (selectedPatient->allTests.at(selectedPatient->allTests.size() - 1).result == 0)
                    labTestResult.caption("\n\n\n\n\n\n\t\t<size=16> negative");

                else
                    labTestResult.caption("\n\n\n\n\n\n\t\t<red bold size=16>POSITIVE");

            }

            });



        });




    //////////




    btnEnterPatient.events().click([&] {
        std::string name;
        std::string age;
        std::string postal;

        int x = 0;


        nameBox.getline(0, name);
        ageBox.getline(0, age);
        postalBox.getline(0, postal);

        if (nameBox.edited() && ageBox.edited() && postalBox.edited()) {

            Patient p(name, age, postal);


            allPatients.push_back(p);
            patientList.push_back(p.name);

            nameBox.select(true);
            nameBox.del();

            ageBox.select(true);
            ageBox.del();

            postalBox.select(true);
            postalBox.del();
        }


        });




    //////////




    btnCalculateStats.events().click([&] {

        std::string strCalc;

        if (formCalcStats == NULL) {
            formCalcStats = new form(API::make_center(200, 250));
            labCalcStats = new label(*formCalcStats);
        }
        else {
            delete formCalcStats;
            delete labCalcStats;
            formCalcStats = new form(API::make_center(200, 250));
            labCalcStats = new label(*formCalcStats);
        }


        std::map<int, int> ageBrackets;
        std::map<std::string, int> postalBrackets;
        int maxAge = 0;



        if (!allPatients.empty()) {

            for (auto aPerson : allPatients) {
                if (std::stoi(aPerson.age) > maxAge)
                    maxAge = std::stoi(aPerson.age);

                int ageBracket = std::stoi(aPerson.age) / 5;
                auto bracketItr = ageBrackets.find(ageBracket);
                if (bracketItr != ageBrackets.end()) { //it exists
                    bracketItr->second++; //one more in this bracket
                }
                else { //no one from this age group yet
                    ageBrackets.insert(std::make_pair(ageBracket, 1));
                }



            }

            strCalc.append("\n\tAge bracket\t | \tNumber of \t\t\t\t\t\t\t\t\t\t\tPatients\n");
            strCalc.append("______________________________________\n\n");

            for (auto pairs : ageBrackets) {
                strCalc.append("\t\t\t" + std::to_string(pairs.first * 5) + "\t\t\t\t\t\t\t" + std::to_string(pairs.second) + "\n");
            }



            labCalcStats->caption(strCalc);
            formCalcStats->div("vert <string1>");
            formCalcStats->operator[]("string1") << (*labCalcStats);
            formCalcStats->collocate();
            formCalcStats->show();


        }




        });





    //////////




    btnHotspots.events().click([&] {

        std::string strHotspots;

        if (formHotspots == NULL) {
            formHotspots = new form(API::make_center(200, 250));
            labHotspots = new label(*formHotspots);
        }
        else {
            delete formHotspots;
            delete labHotspots;
            formHotspots = new form(API::make_center(200, 250));
            labHotspots = new label(*formHotspots);
        }

        std::map<int, int> ageBrackets;
        std::map<std::string, int> postalBrackets;
        int maxAge = 0;



        if (!allPatients.empty()) {

            for (auto aPerson : allPatients) {
                if (std::stoi(aPerson.age) > maxAge)
                    maxAge = std::stoi(aPerson.age);

                std::string firstThreeLetters = aPerson.postalCode.substr(0, 3);
                auto postalBracketItr = postalBrackets.find(firstThreeLetters);
                if (postalBracketItr != postalBrackets.end()) { //it exists
                    postalBracketItr->second++; //one more in this bracket
                }
                else { //no one from this postal group yet
                    postalBrackets.insert(std::make_pair(firstThreeLetters, 1));
                }


            }

            strHotspots.append("\n\tPostal Code\t | \tNumber of \t\t\t\t\t\t\t\t\t\t\tCases\n");
            strHotspots.append("______________________________________\n\n");

            for (auto codes : postalBrackets) {
                strHotspots.append("\t\t\t" + codes.first + "\t\t\t\t\t\t\t" + std::to_string(codes.second) + "\n");
            }

            labHotspots->caption(strHotspots);
            formHotspots->div("vert <string1>");
            formHotspots->operator[]("string1") << (*labHotspots);
            formHotspots->collocate();
            formHotspots->show();


        }




        });








    //end methods












    //Layout management

    fm.div("vert    < <labName> <nameBox> <> <btnHotspots> >      < <labDateOfBirth> <ageBox> <> <btnCalcStats> >       < <labPostalCode> <postalBox> <labTestResult> <btnRunTest> >     < <btnEnterPatient> <list> >       <exit> ");
    //
    fm["labName"] << labName;
    fm["nameBox"] << nameBox;
    fm["btnHotspots"] << btnHotspots;

    fm["labDateOfBirth"] << labDateOfBirth;
    fm["ageBox"] << ageBox;
    fm["btnCalcStats"] << btnCalculateStats;

    fm["labPostalCode"] << labPostalCode;
    fm["postalBox"] << postalBox;

    fm["labTestResult"] << labTestResult;
    fm["btnRunTest"] << btnRunTest;

    fm["btnEnterPatient"] << btnEnterPatient;
    fm["list"] << patientList;


    fm["exit"] << btnExit;



    /////



    fm.collocate();
    //Show the form
    fm.show();
    //Start to event loop process, it blocks until the form is closed.
    exec();
}