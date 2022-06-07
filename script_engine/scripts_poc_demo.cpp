#include "Script.h"

int main() {
    std::string script_text = R"(
    SCRIPT
        SET A 1
        SET B 1
        SET I 1
        SET MAX_STEPS 20
        PRINT 1
        PRINT 1
    ENDSCRIPT

    SCRIPT
        RETURN_IF LESS $MAX_STEPS $I
        ADD I 1
        SET TMP $A
        ADD A $B
        SET B $TMP
        PRINT $A
        REPEAT
    ENDSCRIPT
    )";

    cinder::Script script(script_text);
    
    for (int i=0; i<200; ++i) {
        script.execute_step();
    }
}
