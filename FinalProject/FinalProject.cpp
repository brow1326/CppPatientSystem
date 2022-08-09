// FinalProject.cpp : Defines the entry point for the application.
//

#include "FinalProject.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>

int main()
{
    using namespace nana;

    //Define a form.
    form fm;

    //Define a label and display a text.
    label lab{ fm, "Hello, <bold blue size=16>Nana C++ Library</>" };
    lab.format(true);

    //Define a button and answer the click event.
    button btnExit{ fm, "Quit" };
    btnExit.events().click([&fm] {
        fm.close();
        });

    label labName{ fm, "Full Name: " };
    label labDateOfBirth{ fm, "Date of Birth: " };
    
    button redBtn{ fm, "Enter patient" };
    button btnName{ fm, "Enter Name: " };
    textbox nameBox{ fm };


    btnName.events().click([] {std::cout << "click" << std::endl; });

    button btnDOB{ fm, "Enter Date of Birth: " };
    

    //Layout management
    fm.div("vert        < <labName> <nameBox> >       < <labDateOfBirth> <btnDOB> >      <exit> ");
    fm["labName"] << labName;
    fm["nameBox"] << nameBox;
    fm["labDateOfBirth"] << labDateOfBirth;
    fm["btnDOB"] << btnDOB;

    fm["exit"] << btnExit;



    fm.collocate();

    //Show the form
    fm.show();

    //Start to event loop process, it blocks until the form is closed.
    exec();
}