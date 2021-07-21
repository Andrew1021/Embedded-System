/*
 * FIFO.c
*
*  Created on: 20.12.2020
*      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
*/

#include "../header/FIFO.h"

//*******************************************************
// \brief FIFO write access with busy waiting for free space (blocking function)
// \param *fifo pointer to FIFO struct
// \param data write data
// \return none
//*******************************************************
void Fifo_Write_Busy(fifo_t *fifo, fifo_data_t data)
{
    while(!Fifo_Get_Free(fifo));
    Fifo_Write(fifo, data);
}

//*******************************************************
// \brief FIFO write access without check for free space
// \param *fifo pointer to FIFO struct
// \param data write data
// \return none
//*******************************************************
void Fifo_Write(fifo_t *fifo, fifo_data_t data)
{
    fifo_data_t  *tmp;

    tmp = (fifo_data_t*)fifo->write_p;
    *tmp++ = data;
    if (tmp > fifo->top) {
        fifo->write_p = fifo->base;
    } else {
        fifo->write_p = tmp;
    }
}

//*******************************************************
// \brief FIFO read access with busy waiting for available data (blocking function)
// \param *fifo pointer to FIFO struct
// \return read data
//*******************************************************
fifo_data_t Fifo_Read_Busy(fifo_t *fifo)
{
    while(!Fifo_Get_Level(fifo));
    return Fifo_Read(fifo);
}

//*******************************************************
// \brief FIFO read access without check for available data
// \param *fifo pointer to FIFO struct
// \return read data
//*******************************************************
fifo_data_t Fifo_Read(fifo_t *fifo)
{
    fifo_data_t data;
    fifo_data_t *tmp;


        tmp = (fifo_data_t*)fifo->read_p;
        data = *tmp++;
        if (tmp > fifo->top) {
            fifo->read_p = fifo->base;
        } else {
            fifo->read_p = tmp;
        }
    return data;
}

//*******************************************************
// \brief Get fill level of FIFO
// \param *fifo pointer to FIFO struct
// \return fill level of FIFO in elements
//*******************************************************
fifo_size_t Fifo_Get_Level(fifo_t *fifo)
{
    fifo_size_t tmp;
    fifo_data_t *tmp_w, *tmp_r;

    tmp_w = (fifo_data_t*)fifo->write_p;
    tmp_r = (fifo_data_t*)fifo->read_p;
    tmp = tmp_w - tmp_r;
    if (tmp_w < tmp_r) {
        tmp += fifo->size;
    }
    return tmp;
}

//*******************************************************
// \brief Get free space of fifo
// \param *fifo pointer to FIFO struct
// \return free space of FIFO in elements
//*******************************************************
fifo_size_t Fifo_Get_Free(fifo_t *fifo)
{
    fifo_size_t tmp;
    fifo_data_t *tmp_w, *tmp_r;

        tmp_w = (fifo_data_t*)fifo->write_p;
        tmp_r = (fifo_data_t*)fifo->read_p;
    tmp = tmp_w - tmp_r;
    if (tmp_w < tmp_r) {
        tmp += fifo->size;
    }
    tmp =  fifo->size - tmp - 1;
    return tmp;
}

//*******************************************************
// \brief Get number of elements for write access until pointer wrap around
// \param *fifo pointer to FIFO struct
// \return number of elements for write access until pointer wrap around
//*******************************************************
fifo_size_t Fifo_Get_Write_Wrap(fifo_t *fifo)
{
    fifo_size_t tmp;
    tmp = fifo->top - fifo->write_p + 1;
    return tmp;
}

//*******************************************************
// \brief Get number of elements for read access until pointer wrap around
// \param *fifo pointer to FIFO struct
// \return number of elements for read access until pointer wrap around
//*******************************************************
fifo_size_t Fifo_Get_Read_Wrap(fifo_t *fifo)
{
    fifo_size_t tmp;
    tmp = fifo->top - fifo->read_p + 1;
    return tmp;
}

//*******************************************************
// \brief FIFO initialization
// \brief FIFO can hold only size-1 elements! One element is unused due to organization.
// \param *fifo pointer to FIFO struct
// \param *data pointer to data buffer
// \param size size of data buffer in elements
// \return none
//*******************************************************
void Fifo_Init(fifo_t *fifo, fifo_data_t *data, fifo_size_t size)
{
    fifo->write_p = data;
    fifo->read_p  = data;
    fifo->base    = data;
    fifo->top     = data + size - 1;
    fifo->size    = size;
}

