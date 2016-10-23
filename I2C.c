#include "I2C.h"

bool open(uint openMode){
    	uint flags = 0;

        if( (openMode & ReadOnly)   == ReadOnly     ){  flags |= O_RDONLY;  }
        if( (openMode & WriteOnly)  == WriteOnly    ){  flags |= O_WRONLY;  }
        if( (openMode & ReadWrite)  == ReadWrite    ){  flags |= O_RDWR;    }
        if( (openMode & Append)     == Append       ){  flags |= O_APPEND;  }
        if( (openMode & Truncate)   == Truncate     ){  flags |= O_TRUNC;   }
        if( (openMode & NonBlock)   == NonBlock     ){  flags |= O_NONBLOCK;}

        if( ::open(this->i2cPortPath.c_str(), flags) < 0){
		return false;
	}

        return true;
}

bool close()
{
        if( ::close(this->i2cFD) < 0 )
        {
            this->i2cErrors->closeError = true;
            return false;
        }
        else
        {
            this->i2cErrors->closeError = false;
            this->isOpenFlag = false;
            return true;
        }
}

bool useSmbusIOCTL(direction rwMode, uint8_t registerAddr, transactionType smbusTransaction, i2c_smbus_data &data, unsigned int i2cDeviceAddress)
{
        if( rwMode == bothDirection ) { return false; }

        i2c_smbus_ioctl_data smbusPackage;

        smbusPackage.read_write = (rwMode == input ) ? I2C_SMBUS_READ : I2C_SMBUS_WRITE;
        smbusPackage.command    = registerAddr;
        smbusPackage.size       = smbusTransaction;
        smbusPackage.data       = &data;

	/*
	setSlave's functionality
	*/
        if( ::ioctl(this->i2cFD, I2C_SLAVE, i2cDevAddress) < 0)
        {
            return false;
        }

        if( ::ioctl(this->i2cFD, I2C_SMBUS, &smbusPackage) < 0 )
        {
            return false;
        }
        
	return true;
}

bool writeBlock(bus, device_adress, reg_address, pointer to data block, numBytes) <- pointer is in
bool read(bus, device_adress, reg_address, pointer to data block, numBytes) <- pointer is out


