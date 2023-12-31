//
// Created by laqieer on 2020/1/1.
//

#ifndef FE7_JP_STUNNING_TRIBBLE_PROC_H
#define FE7_JP_STUNNING_TRIBBLE_PROC_H

#include <gba_types.h>

struct Proc;

typedef void (*ProcFunc)(struct Proc *);

struct ProcCmd
{
    s16 opcode;
    s16 dataImm;
    void *dataPtr;
};

#define PROC_END                                     { 0x00, 0x0000, 0 }
#define PROC_SET_NAME(aName)                         { 0x01, 0x0000, aName }
#define PROC_CALL_ROUTINE(apRoutine)                 { 0x02, 0x0000, (void*)(apRoutine) }
#define PROC_LOOP_ROUTINE(apRoutine)                 { 0x03, 0x0000, (void*)(apRoutine) }
#define PROC_SET_DESTRUCTOR(apRoutine)               { 0x04, 0x0000, (void*)(apRoutine) }
#define PROC_NEW_CHILD(ap6CChild)                    { 0x05, 0x0000, (void*)(ap6CChild) }
#define PROC_NEW_CHILD_BLOCKING(ap6CChild)           { 0x06, 0x0000, (void*)(ap6CChild) }
#define PROC_NEW_MAIN_BUGGED(ap6CMain)               { 0x07, 0x0000, ap6CMain }
#define PROC_WHILE_EXISTS(ap6CToCheck)               { 0x08, 0x0000, (void*)(ap6CToCheck) }
#define PROC_END_ALL(ap6CToCheck)                    { 0x09, 0x0000, (void*)(ap6CToCheck) }
#define PROC_BREAK_ALL_LOOP(ap6CToCheck)             { 0x0A, 0x0000, (void*)(ap6CToCheck) }
#define PROC_LABEL(aLabelId)                         { 0x0B, aLabelId, 0 }
#define PROC_GOTO(aLabelId)                          { 0x0C, aLabelId, 0 }
#define PROC_JUMP(ap6CCode)                          { 0x0D, 0x0000, (void*)(ap6CCode) }
#define PROC_SLEEP(aTime)                            { 0x0E, aTime,  0 }
#define PROC_SET_MARK(aMark)                         { 0x0F, aMark,  0 }
#define PROC_BLOCK                                   { 0x10, 0x0000, 0 }
#define PROC_END_IF_DUPLICATE                        { 0x11, 0x0000, 0 }
#define PROC_SET_BIT4                                { 0x12, 0x0000, 0 }
#define PROC_13                                      { 0x13, 0x0000, 0 }
#define PROC_WHILE_ROUTINE(aprRoutine)               { 0x14, 0x0000, (void*)(aprRoutine) }
#define PROC_15                                      { 0x15, 0x0000, 0 }
#define PROC_CALL_ROUTINE_2(aprRoutine)              { 0x16, 0x0000, (void*)(aprRoutine) }
#define PROC_END_DUPLICATES                          { 0x17, 0x0000, 0 }
#define PROC_CALL_ROUTINE_ARG(aprRoutine, aArgument) { 0x18, aArgument, (void*)(aprRoutine) }
#define PROC_19                                      { 0x19, 0x0000, 0 }
#define PROC_YIELD                                   PROC_SLEEP(0)

// allows local Proc structs to invoke the general Proc
// fields when creating local Proc definitions.
#define PROC_HEADER                                                                  \
    const struct ProcCmd *script; /*pointer to process script*/                      \
    const struct ProcCmd *currCmd; /*pointer to currently executing script command*/ \
    ProcFunc onDelete; /*callback to run upon delegint the process*/                 \
    ProcFunc nativeFunc; /*callback to run once each frame.*/                        \
                         /*disables script execution when not null*/                 \
    char *name;                                                                      \
    struct Proc *parent; /*pointer to parent proc. If this proc is a root proc,*/    \
                         /*this member is an integer which is the root index.*/      \
    struct Proc *child; /*pointer to most recently added child*/                     \
    struct Proc *next; /*next sibling*/                                              \
    struct Proc *prev; /*previous sibling*/                                          \
    s16 sleepTime;                                                                   \
    u8 mark;                                                                         \
    u8 flags;                                                                        \
    u8 blockSemaphore; /*wait semaphore. Process execution*/                         \
                       /*is blocked when this is nonzero.*/                          \

// size: 0x6C bytes
struct Proc
{
    PROC_HEADER
    /*0x29*/ u8 data[67]; // this section is to be used in locally defined proc structs for use by specific files.
};

enum {
    PROC_MARK_0 = 0,
    PROC_MARK_1 = 1,
    PROC_MARK_2 = 2,
    PROC_MARK_3 = 3,
    PROC_MARK_4 = 4,
    PROC_MARK_5 = 5,
    PROC_MARK_6 = 6,
    PROC_MARK_7 = 7
};

#define ROOT_PROC_0 (struct Proc *)0
#define ROOT_PROC_1 (struct Proc *)1
#define ROOT_PROC_2 (struct Proc *)2
#define ROOT_PROC_3 (struct Proc *)3
#define ROOT_PROC_4 (struct Proc *)4
#define ROOT_PROC_5 (struct Proc *)5
#define ROOT_PROC_6 (struct Proc *)6
#define ROOT_PROC_7 (struct Proc *)7

struct Proc* Proc_Find(const struct ProcCmd* script);
void Proc_Break(struct Proc* proc);
struct Proc *Proc_StartBlocking(const struct ProcCmd* script, u32 parent);
struct Proc *Proc_Start(const struct ProcCmd* script, u32 parent);
void EndProc(struct Proc *proc);
void GotoProcLabel(struct Proc *proc, u16 label);
void func8003fd4(int a, int b, int c, int d, int e);

#endif //FE7_JP_STUNNING_TRIBBLE_PROC_H
