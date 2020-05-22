#include "CUIText.h"

std::string CUIText::Intro = "\033[0;32m"
                             "        ╔═════════════╗\n"
                             "        ║ M a t r i x ║\n"
                             "    ╔═══╩═════════════╩═══╗\n"
                             "    ║ c a l c u l a t o r ║\n"
                             "    ╩═════════════════════╩\n"
                             "───────────────────────────────"
                             "\033[0m";
std::string CUIText::Outro = "\033[0;32m"
                             " Stopping matrix calculator..."
                             "\033[0m\n";
std::string CUIText::Prefix = "\033[0;32mMC >\033[0m ";

CUIText::MyMap CUIText::mainCommands = {
        { EKey::HELP ,       "HELP" } ,
        { EKey::SCAN ,       "SCAN" } ,
        { EKey::LOAD ,       "LOAD" } ,
        { EKey::SAVE ,       "SAVE" } ,
        { EKey::PRINT ,      "PRINT" } ,
        { EKey::CALCULATE ,  "CAL" } ,
        { EKey::DELETE ,     "DELETE" } ,
        { EKey::DELETE_ALL , "DELETE_ALL" } ,
        { EKey::EXIT ,       "EXIT" }
};

CUIText::MyMap CUIText::calculateCommands = {
        { EKey::HORIZONTAL_MERGE , "MERGE_H" } ,
        { EKey::VERTICAL_MERGE ,   "MERGE_V" } ,
        { EKey::TRANSPOSE ,        "TRANS" } ,
        { EKey::INVERSE ,          "INVERSE" } ,
        { EKey::GEM ,              "GEM" } ,
        { EKey::GEM_INFO ,         "GEM_INFO" } ,
        { EKey::CUT ,              "CUT" } ,
        { EKey::DETERMINANT ,      "DET" } ,
        { EKey::RANGE ,            "RAN" }
};
CUIText::MyMap CUIText::messages = {
        { EKey::SCAN ,       "\033[0;32mMatrix has been scanned.\033[0m\n" } ,
        { EKey::DELETE ,     "\033[0;32mMatrix was deleted.\033[0m\n" } ,
        { EKey::DELETE_ALL , "\033[0;32mAll matrices were deleted.\033[0m\n" } ,
        { EKey::LOAD ,       "\033[0;32mMatrices have been loaded.\033[0m\n" } ,
        { EKey::SAVE ,       "\033[0;32mMatrices have been saved.\033[0m\n" }
};

CUIText::MyMap CUIText::helpText = {
        { EKey::APP ,        "AVAILABLE COMMANDS:\n"
                             "\t- '" + mainCommands.at ( EKey::HELP ) + "' \t\t PRINT a commands info\n" +
                             "\t- '" + mainCommands.at ( EKey::SCAN ) + "' \t\t SCAN a new matrix from\n" +
                             "\t- '" + mainCommands.at ( EKey::LOAD ) + "' \t\t LOAD matrices from the file\n" +
                             "\t- '" + mainCommands.at ( EKey::SAVE ) + "' \t\t SAVE matrices to the file\n" +
                             "\t- '" + mainCommands.at ( EKey::PRINT ) + "' \t\t PRINT a matrix\n" +
                             "\t- '" + mainCommands.at ( EKey::CALCULATE ) + "' \t\t CALCULATE with a matrix\n" +
                             "\t- '" + mainCommands.at ( EKey::DELETE ) + "' \t\t delete variable\n" +
                             "\t- '" + mainCommands.at ( EKey::DELETE_ALL ) + "' \t\t delete all variable\n" +
                             "\t- '" + mainCommands.at ( EKey::EXIT ) + "' \t\t EXIT program\n" +
                             "\n" +
                             "for more info type " + CUIText::mainCommands.at ( EKey::HELP ) + " 'COMMAND'\n" +
                             "\n\tsyntax : \033[0;32m" + CUIText::mainCommands.at ( EKey::HELP ) + " [command]\033[0m\n" } ,

        { EKey::HELP ,       "COMMAND " + mainCommands.at ( EKey::HELP ) + ":\n" +
                             "\t- Command " + mainCommands.at ( EKey::HELP ) + " displays available commands.\n" +
                             "\t- You can type " + mainCommands.at ( EKey::HELP ) + " 'COMMAND' for more info about specific command\n" +
                             "\n\tsyntax : \033[0;32m" + mainCommands.at ( EKey::HELP ) + " [command]\033[0m\n" } ,
        { EKey::SCAN ,       "COMMAND " + mainCommands.at ( EKey::SCAN ) + ":\n" +
                             "\t- Command '" + mainCommands.at ( EKey::SCAN ) + "' scans matrix.\n" +
                             "\n\tsyntax : \033[0;32m" + mainCommands.at ( EKey::SCAN ) +
                             " [variable of matrix] [height] [width]'\033[0m - [variable of name] must contains only a-z\n" } ,
        { EKey::LOAD ,       "COMMAND " + mainCommands.at ( EKey::LOAD ) + ":\n" +
                             "\t- Command '" + mainCommands.at ( EKey::LOAD ) + "' LOAD matrices from the file.\n" +
                             "\n\t syntax : \033[0;32m" + mainCommands.at ( EKey::LOAD ) + " [path_to_file]\033[0m\n" } ,
        { EKey::SAVE ,       "COMMAND " + mainCommands.at ( EKey::SAVE ) + ":\n" +
                             "\t- Command '" + mainCommands.at ( EKey::SAVE ) + "' SAVE matrices from the file.\n" +
                             "\n\t syntax : \033[0;32m" + mainCommands.at ( EKey::SAVE ) + " [path_to_file]\033[0m\n" } ,
        { EKey::PRINT ,      "COMMAND " + mainCommands.at ( EKey::PRINT ) + ":\n" +
                             "\t- Command '" + mainCommands.at ( EKey::PRINT ) + "' prints matrix out.\n" +
                             "\n\tsyntax : \033[0;32m" + mainCommands.at ( EKey::PRINT ) + " [variable of matrix to PRINT]\033[0m\n" } ,
        { EKey::CALCULATE ,  "COMMAND " + mainCommands.at ( EKey::CALCULATE ) + ":\n" +
                             "\t- Command '" + mainCommands.at ( EKey::CALCULATE ) + "' with calculates matrix.\n" +
                             "\t- Use this command every time you CALCULATE, work, modify with matrix.\n" +
                             "\n\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) +
                             " [variable] = [variable] [+,-,*] [variable]\033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + " [variable] = [variable] " +
                             calculateCommands.at ( EKey::HORIZONTAL_MERGE ) + " [variable]\033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + " [variable] = [variable] " +
                             calculateCommands.at ( EKey::VERTICAL_MERGE ) + " [variable]\033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + " [variable] = " +
                             calculateCommands.at ( EKey::TRANSPOSE ) +
                             " [variable]\033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + " [variable] = INVERSE [variable]\033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + " [variable] = " + calculateCommands.at ( EKey::GEM ) +
                             " [variable]\033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + ' ' + calculateCommands.at ( EKey::GEM_INFO ) +
                             " [variable]\033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + " [variable] = " + calculateCommands.at ( EKey::CUT ) +
                             " [variable] [i0] [i1] [j0] [j1] \033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + ' ' + calculateCommands.at ( EKey::DETERMINANT ) +
                             " [variable]\033[0m\n" +
                             "\t syntax : \033[0;32m" + mainCommands.at ( EKey::CALCULATE ) + ' ' + calculateCommands.at ( EKey::RANGE ) +
                             " [variable]\033[0m\n" } ,
        { EKey::DELETE ,     "COMMAND " + mainCommands.at ( EKey::DELETE ) + ":\n" +
                             "\t- Command '" + mainCommands.at ( EKey::DELETE ) + "' delete previous used variable.\n" +
                             "\n\t syntax : \033[0;32m" + mainCommands.at ( EKey::DELETE ) + " [variable]\033[0m\n" } ,
        { EKey::DELETE_ALL , "COMMAND " + mainCommands.at ( EKey::DELETE_ALL ) + ":\n" +
                             "\t- Command '" + mainCommands.at ( EKey::DELETE_ALL ) + "' delete all previous used variable.\n" +
                             "\n\t syntax : \033[0;32m" + mainCommands.at ( EKey::DELETE_ALL ) + "\033[0m\n" } ,
        { EKey::EXIT ,       "COMMAND " + mainCommands.at ( EKey::EXIT ) + ":\n"
                                                                           "\t- Command '" + mainCommands.at ( EKey::EXIT ) +
                             "' EXIT application matrix calculator.\n" }
};
CUIText::MyMap CUIText::error = {
        { EKey::UNKNOWN_COMMAND , "Unknown command.\nType '" + mainCommands.at ( EKey::HELP ) + "' for mor info.\n" } ,
        { EKey::INVALID_SYNTAX ,  "Invalid syntax.\nType '" + mainCommands.at ( EKey::HELP ) + " [command]' for mor info.\n" } ,
        { EKey::LOAD ,            "Matrices could not have been loaded from the file.\nType '" + mainCommands.at ( EKey::LOAD ) +
                                  " [command]' for mor info.\n" } ,
        { EKey::SAVE ,            "Matrices could not have been saved from the file.\nType '" + mainCommands.at ( EKey::SAVE ) +
                                  " [command]' for mor info.\n" } ,
        { EKey::NO_VAR ,          "There is no such matrices.\n" } ,
        { EKey::INVALID_INPUT ,   "Invalid input.\n" } ,
        { EKey::DIMENSION ,       "Invalid size of matrix.\n" } ,
        { EKey::MATH ,            "This operation in not defined in MATH.\n" } ,
        { EKey::STH_ELSE , "Something went wrong, please check you input.\n You can contact developer <trojaj12@fit.cvut.cz>.\n" }
};
