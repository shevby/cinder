#include "Script.h"

int main() {
    std::string script_text =
    "SCRIPT\n"
    "    ASSIGN_VALUE A 1\n"
    "    ASSIGN_VALUE B 1\n"
    "    ASSIGN_VALUE I 1\n"
    "    ASSIGN_VALUE MAX_STEPS 20\n"
    "    ASSIGN_VALUE ONE 1\n"
    "    PRINT ONE\n"
    "    PRINT ONE\n"
    "ENDSCRIPT\n"
    "\n"
    "SCRIPT\n"
    "    RETURN_IF LESS MAX_STEPS I\n"
    "    ADD I ONE\n"
    "    ASSIGN_VARIABLE TMP A\n"
    "    ADD A B\n"
    "    ASSIGN_VARIABLE B TMP\n"
    "    PRINT A\n"
    "    REPEAT\n"
    "ENDSCRIPT\n";

    cinder::Script script(script_text);
    
    for (int i=0; i<200; ++i) {
        script.execute_step();
    }
}
