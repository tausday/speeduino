#include "globals.h"

#define STEPPER_FORWARD 0
#define STEPPER_BACKWARD 1
#define IDLE_TABLE_SIZE 10

enum StepperStatus {SOFF, STEPPING, COOLING}; //The 2 statuses that a stepper can have. STEPPING means that a high pulse is currently being sent and will need to be turned off at some point.

struct StepperIdle
{
  unsigned short curIdleStep; //Tracks the current location of the stepper
  unsigned short targetIdleStep; //What the targetted step is
  volatile StepperStatus stepperStatus; 
  volatile unsigned long stepStartTime; //The time the curren
};

struct table2D iacClosedLoopTable;
struct table2D iacPWMTable;
struct table2D iacStepTable;
//Open loop tables specifically for cranking
struct table2D iacCrankStepsTable;
struct table2D iacCrankDutyTable;

struct StepperIdle idleStepper;
bool idleOn; //Simply tracks whether idle was on last time around
unsigned short iacStepTime;

volatile byte *idle_pin_port;
volatile byte idle_pin_mask;
volatile byte *idle2_pin_port;
volatile byte idle2_pin_mask;
volatile bool idle_pwm_state;
unsigned short idle_pwm_max_count; //Used for variable PWM frequency
volatile unsigned short idle_pwm_cur_value;
long idle_pwm_target_value;
long idle_cl_target_rpm;

void initialiseIdle();
static inline void disableIdle();
static inline void enableIdle();
