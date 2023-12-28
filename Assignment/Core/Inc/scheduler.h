/*
 * scheduler.h
 *
 *  Created on: Nov 25, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include"main.h"


#endif /* INC_SCHEDULER_H_ */
 void SCH_Init(void);

 void SCH_Update(void);
 void SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD);

 void SCH_Dispatch_Tasks(void);

 void SCH_Delete_Task(uint32_t TASK_ID);
