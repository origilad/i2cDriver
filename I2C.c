int i2cFD;

typedef int bool;
#define true 1
#define false 0 

#include "I2C.h"
#include <stdio.h>


bool _I2CLIB_open(unsigned int openMode, i2cName i2c){
  unsigned int flags = 0;

  char * str;
  sprintf(str, "%d", ((int)(i2c)));
  unsigned char * i2cPortPath   = "/dev/i2c-" + *str;

    
  if( (openMode & ReadOnly)   == ReadOnly     ){  flags |= O_RDONLY;  }
  if( (openMode & WriteOnly)  == WriteOnly    ){  flags |= O_WRONLY;  }
  if( (openMode & ReadWrite)  == ReadWrite    ){  flags |= O_RDWR;    }
  if( (openMode & Append)     == Append       ){  flags |= O_APPEND;  }
  if( (openMode & Truncate)   == Truncate     ){  flags |= O_TRUNC;   }
  if( (openMode & NonBlock)   == NonBlock     ){  flags |= O_NONBLOCK;}

  i2cFD = open(i2cPortPath, flags);

	if(i2cFD < 0){
		return false;
	}

        return true;
}

bool _I2CLIB_close()
{
        if(close(i2cFD) < 0 )
        {
            return false;
        }
        else
        {
            return true;
        }
}

bool _I2CLIB_useSmbusIOCTL(direction rwMode, uint8_t registerAddr, transactionType smbusTransaction, union i2c_smbus_data *data, unsigned int i2cDeviceAddress)
{
        if( rwMode == bothDirection ) { return false; }

        struct i2c_smbus_ioctl_data smbusPackage;

        smbusPackage.read_write = (rwMode == input ) ? I2C_SMBUS_READ : I2C_SMBUS_WRITE;
        smbusPackage.command    = registerAddr;
        smbusPackage.size       = smbusTransaction;
        smbusPackage.data       = data;

	/*
	setSlave's functionality
	*/
        if(ioctl(i2cFD, I2C_SLAVE, i2cDeviceAddress) < 0)
        {
            return false;
        }

        if(ioctl(i2cFD, I2C_SMBUS, &smbusPackage) < 0 )
        {
            return false;
        }
        
	return true;
}

bool I2CLIB_writeBlock(i2cName i2c, uint8_t reg_address, union i2c_smbus_data *data, transactionType numBytes, unsigned int i2cDeviceAddress)
{
	_I2CLIB_open(WriteOnly, i2c);
	_I2CLIB_useSmbusIOCTL(I2C_SMBUS_WRITE, reg_address, numBytes, data, i2cDeviceAddress);  	
	_I2CLIB_close();
}
bool I2CLIB_read(i2cName i2c, uint8_t reg_address, union i2c_smbus_data *data, transactionType numBytes, unsigned int i2cDeviceAddress)
{
	_I2CLIB_open(ReadOnly, i2c);
	_I2CLIB_useSmbusIOCTL(I2C_SMBUS_READ, reg_address, numBytes, data, i2cDeviceAddress);  	
	_I2CLIB_close();
}
