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

inline bool setSlave();

bool open(uint openMode);

bool close();

inline bool useSmbusIOCTL( direction rwMode, uint8_t registerAddr,
  transactionType smbusTransaction, i2c_smbus_data &data, unsigned int i2cDeviceAddress );

bool writeBlock( bus, device_adress, reg_address, pointer to data block, numBytes );

bool read( bus, device_adress, reg_address, pointer to data block, numBytes );
