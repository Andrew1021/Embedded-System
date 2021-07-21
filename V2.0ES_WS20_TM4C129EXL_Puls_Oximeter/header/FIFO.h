/*
* FIFO.h
*
*  Created on: 20.12.2020
*      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
*/

#ifndef HEADER_FIFO_H_
#define HEADER_FIFO_H_

#include <stdint.h>

//*******************************************************
// \defgroup FIFO_CONFIGURATION FIFO CONFIGURATION
// Define the data type for your FIFO data \n
// Define the size of your FIFO size\n
//*******************************************************
/*@{*/

typedef uint16_t fifo_data_t;       /**< FIFO data element type */
typedef uint16_t fifo_size_t;       /**< FIFO size type */

/*@}*/

//*******************************************************
// \struct fifo_t Fifo.h "Fifo.h"
// \brief FIFO control data struct
//
//*******************************************************
typedef struct {
fifo_data_t * write_p; /**< write pointer */
fifo_data_t * read_p;  /**< read pointer */
fifo_data_t * base;    /**< base pointer */
fifo_data_t * top;     /**< top pointer */
fifo_size_t size;      /**< size */
} fifo_t;

//*******************************************************
// \brief FIFO initialization
// \brief FIFO can hold only size-1 elements! One element is unused due to organization.
// \param *fifo pointer to FIFO struct
// \param *data pointer to data buffer
// \param size size of data buffer in elements
// \return none
//*******************************************************
void Fifo_Init(fifo_t *fifo, fifo_data_t *data, fifo_size_t size);

//*******************************************************
// \brief FIFO write access without check for free space
// \param *fifo pointer to FIFO struct
// \param data write data
// \return none
//*******************************************************
void Fifo_Write(fifo_t *fifo, fifo_data_t data);

//*******************************************************
// \brief FIFO write access with busy waiting for free space (blocking function)
// \param *fifo pointer to FIFO struct
// \param data write data
// \return none
//*******************************************************
void Fifo_Write_Busy(fifo_t *fifo, fifo_data_t data);

//*******************************************************
// \brief FIFO read access with busy waiting for available data (blocking function)
// \param *fifo pointer to FIFO struct
// \return read data
//*******************************************************
fifo_data_t Fifo_Read_Busy(fifo_t *fifo);

//*******************************************************
// \brief FIFO read access without check for available data
// \param *fifo pointer to FIFO struct
// \return read data
//*******************************************************
fifo_data_t Fifo_Read(fifo_t *fifo);

//*******************************************************
// \brief Get fill level of FIFO
// \param *fifo pointer to FIFO struct
// \return fill level of FIFO in elements
//*******************************************************
fifo_size_t Fifo_Get_Level(fifo_t *fifo);

//*******************************************************
// \brief Get free space of fifo
// \param *fifo pointer to FIFO struct
// \return free space of FIFO in elements
//*******************************************************
fifo_size_t Fifo_Get_Free(fifo_t *fifo);

//*******************************************************
// \brief Get number of elements for write access until pointer wrap around
// \param *fifo pointer to FIFO struct
// \return number of elements for write access until pointer wrap around
//*******************************************************
fifo_size_t Fifo_Get_Write_Wrap(fifo_t *fifo);

//*******************************************************
// \brief Get number of elements for read access until pointer wrap around
// \param *fifo pointer to FIFO struct
// \return number of elements for read access until pointer wrap around
//*******************************************************
fifo_size_t Fifo_Get_Read_Wrap(fifo_t *fifo);

#endif /* HEADER_FIFO_H_ */
