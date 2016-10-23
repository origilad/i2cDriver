#ifndef I2C_H_
#define I2C_H_

/*!
 * This enum is used for selecting file open mode.
 */
enum openMode           {   ReadOnly                = 0,
                            WriteOnly               = 1,
                            ReadWrite               = 2,
                            Append                  = 4,
                            Truncate                = 8,
                            NonBlock                = 16
                        };

inline bool _I2CLIB_setSlave();

int _I2CLIB_open(unsigned int openMode, i2cName i2c );

int _I2CLIB_close();

int _I2CLIB_useSmbusIOCTL( direction rwMode, unsigned int8_t registerAddr,
  transactionType smbusTransaction, i2c_smbus_data &data, unsigned int i2cDeviceAddress );

int I2CLIB_writeBlock(i2cName i2c, unsigned int8_t reg_address, i2c_smbus_data data, transactionType numBytes, unsigned int i2cDeviceAddress)

int I2CLIB_read(i2cName i2c, unsigned int8_t reg_address, i2c_smbus_data data, transactionType numBytes, unsigned int i2cDeviceAddress)
