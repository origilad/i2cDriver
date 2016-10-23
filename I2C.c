bool    BlackI2C::open(uint openMode)
    {
        uint flags = 0;

        if( (openMode & ReadOnly)   == ReadOnly     ){  flags |= O_RDONLY;  }
        if( (openMode & WriteOnly)  == WriteOnly    ){  flags |= O_WRONLY;  }
        if( (openMode & ReadWrite)  == ReadWrite    ){  flags |= O_RDWR;    }
        if( (openMode & Append)     == Append       ){  flags |= O_APPEND;  }
        if( (openMode & Truncate)   == Truncate     ){  flags |= O_TRUNC;   }
        if( (openMode & NonBlock)   == NonBlock     ){  flags |= O_NONBLOCK;}


        this->i2cFD = ::open(this->i2cPortPath.c_str(), flags);


        if( this->i2cFD < 0 )
        {
            this->isOpenFlag = false;
            this->i2cErrors->openError = true;
            return false;
        }
        else
        {
            this->isOpenFlag = true;
            this->i2cErrors->openError = false;
            this->setSlave();
            return true;
        }
    }

    bool    BlackI2C::close()
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

inline bool BlackI2C::useSmbusIOCTL(direction rwMode, uint8_t registerAddr, transactionType smbusTransaction, i2c_smbus_data &data)
    {
        if( rwMode == bothDirection ) { return false; }

        i2c_smbus_ioctl_data smbusPackage;

        smbusPackage.read_write = (rwMode == input ) ? I2C_SMBUS_READ : I2C_SMBUS_WRITE;
        smbusPackage.command    = registerAddr;
        smbusPackage.size       = smbusTransaction;
        smbusPackage.data       = &data;


        if( ::ioctl(this->i2cFD, I2C_SMBUS, &smbusPackage) < 0 )
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool    BlackI2C::setSlave()
    {
        if( ::ioctl(this->i2cFD, I2C_SLAVE, this->i2cDevAddress) < 0)
        {
            this->i2cErrors->setSlaveError = true;
            return false;
        }
        else
        {
            this->i2cErrors->setSlaveError = false;
            return true;
        }
    }
