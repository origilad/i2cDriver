/*!
 * This enum is used for selecting file open mode.
 */
typedef enum            {   ReadOnly                = 0,
                            WriteOnly               = 1,
                            ReadWrite               = 2,
                            Append                  = 4,
                            Truncate                = 8,
                            NonBlock                = 16
                        }openMode;

/*!
 * This enum is used for setting i2c name.
 */
typedef enum            {   I2C_0                   = 0,
                            I2C_1                   = 1
                        }i2cName;

/*!
 *  This enum is used for selecting direction.
 */
typedef enum            {   input                   = 1,
                            output                  = 2,
                            bothDirection           = (input|output)
                        }direction;

/*!
 * This enum is used for selecting i2c bus transaction type.
 */
typedef enum            {   SMBUS_QUICK             = 0,
                            SMBUS_BYTE              = 1,
                            SMBUS_BYTE_DATA         = 2,
                            SMBUS_WORD_DATA         = 3,
                            SMBUS_PROC_CALL         = 4,
                            SMBUS_BLOCK_DATA        = 5,
                            SMBUS_I2C_BLOCK_BROKEN  = 6,
                            SMBUS_BLOCK_PROC_CALL   = 7,
                            SMBUS_I2C_BLOCK_DATA    = 8
                        }transactionType;

inline bool _I2CLIB_setSlave();

int _I2CLIB_open(unsigned int openMode, i2cName i2c );

int _I2CLIB_close();

int _I2CLIB_useSmbusIOCTL( direction rwMode, unsigned int8_t registerAddr,
  transactionType smbusTransaction, i2c_smbus_data &data, unsigned int i2cDeviceAddress );

int I2CLIB_writeBlock(i2cName i2c, unsigned int8_t reg_address, i2c_smbus_data data, transactionType numBytes, unsigned int i2cDeviceAddress)

int I2CLIB_read(i2cName i2c, unsigned int8_t reg_address, i2c_smbus_data data, transactionType numBytes, unsigned int i2cDeviceAddress)
