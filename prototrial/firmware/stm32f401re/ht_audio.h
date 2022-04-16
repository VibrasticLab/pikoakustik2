/**
 * @file    ht_audio.h
 * @brief   Audio Generator header.
 *
 * @addtogroup Audio
 * @{
 */

#ifndef HT_AUDIO_H
#define HT_AUDIO_H

#endif // HT_AUDIO_H

/**
 * @brief GPIO Port to enables Audio DAC
 */
#define AUDIO_IO    GPIOC

/**
 * @brief Pin to enables LEFT Audio DAC on GPIOC.9
 */
#define AUDIO_L     9

/**
 * @brief Pin to enables RIGHT Audio DAC on GPIOC.8
 */
#define AUDIO_R     8

/**
 * @brief Play Left Audio DAC
 */
#define OUT_LEFT    0

/**
 * @brief Play Right Audio DAC
 */
#define OUT_RIGHT   1

/**
 * @brief Default Attenuation scale
 * @details Dont increase as it will make noise more prominent
 */
#define DEFAULT_ATTEN 0.01

/**
 * @brief Default Minimum threshold of 16-bit amplitude
 */
#define DEFAULT_AMPL_THD 1

/**
 * @brief I2S protocol buffer size
 * @details If I2S-SPI and MMC-SPI use same DMA stream, set to 512.
 *          Please check DMA stream ID on both SPI peripherals.
 */
#define I2S_BUFF_SIZE   512

/**
 * @brief Total buffer size
 * @details Just fill it below 44100
 */
#define TOTAL_BUFF_SIZE I2S_BUFF_SIZE*16

/**
 * @brief Wheter use Left/Right or Mono array
 */
#define USE_STEREO_ARRAY TRUE

/**
 * @brief Global Duration for Testing
 * @details Range is 1 to 250 while 100 means 1000ms
 */
#define TEST_DURATION   20 // 200 ms each tone

/**
 * @brief Smallest signal scale can produced as far for now
 * @details Note this use DEFAULT_ATTEN at 0.01
 * @details So signal value is SMALLEST_DB*DEFAULT_ATTEN*32767=1
 */
#define SMALLEST_DB     0.0031

/**
 * @brief First dB ratio for normal ears
 * @details The value ratio follows:\n
 *          9: ratio = 1\n
 *          8: ratio = 0.5\n
 *          7: ratio = 0.25\n
 *          6: ratio = 0.125\n
 *          5: ratio = 0.0625\n
 *          4: ratio = 0.0312\n
 *          3: ratio = 0.0156\n
 *          2: ratio = 0.0078\n
 *          1: ratio = 0.0039\n
 * @details This current value corespond to scale 6
 */
#define NORMALTEST_DB   0.125

/**
 * @brief First dB ratio for actual ears
 * @details The value follow previous documentation
 */
#define ACTUALTEST_DB   1

/**
 * @brief First dB scale at first step on audiotest
 */
#define FIRSTTEST_DB     NORMALTEST_DB

/**
 * @brief Initiate Audio driver via I2S
 */
void ht_audio_Init(void);

/**
 * @brief Generate sine wave with only zero
 */
void ht_audio_Zero(void);

/**
 * @brief Generate sine wave tone from halving formula with Frequency and Amplitude
 * @details This function intended to be actual implementaion of sample preparation
 * @param[in] double Sine wave sample frequency in linear scaling from 400Hz (0.25,0.5,1,2,4,8,16,32) -> 500Hz=1.25
 * @param[in] double Sine wave sample amplitude in linear scaling from 100dB (1 ~ 0.0001 or use ht_audio_Zero())
 */
void ht_audio_Tone(double freq, double ampl);

/**
 * @brief Generate sine wave tone from halving formula with Frequency and Amplitude without any Attenuation
 * @details This function intended to be actual implementaion of sample preparation
 * @param[in] double Sine wave sample frequency in linear scaling from 400Hz (0.25,0.5,1,2,4,8,16,32) -> 500Hz=1.25
 * @param[in] double Sine wave sample amplitude in linear scaling from 100dB (1 ~ 0.0001 or use ht_audio_Zero())
 */
void ht_audio_ToneNoAtt(double freq, double ampl);

/**
 * @brief Generate sine wave tone from halving formula with Frequency and Amplitude
 * @details This function intended to be actual implementaion of sample preparation
 * @param[in] double Sine wave sample frequency in linear scaling from 400Hz (0.25,0.5,1,2,4,8,16,32) -> 500Hz=1.25
 * @param[in] double Sine wave sample amplitude scale in linear scaling from 9 to 1 (9 is loudest)
 */
void ht_audio_ToneScale(double freq, double scale);

/**
 * @brief Generate sine wave tone from halving formula with Frequency and  without any Attenuation
 * @details This function intended to be actual implementaion of sample preparation
 * @param[in] double Sine wave sample frequency in linear scaling from 400Hz (0.25,0.5,1,2,4,8,16,32) -> 500Hz=1.25
 * @param[in] double Sine wave sample amplitude scale in linear scaling from 9 to 1 (9 is loudest)
 */
void ht_audio_ToneScaleNoAtt(double freq, double scale);

/**
 * @brief Play Audio via I2S
 * @details Play I2S Transmit buffer in loop
 * @param[in] uint8_t Duration to play loop (milliseconds)
 */
void ht_audio_Play(uint16_t duration);

/**
 * @brief Disable both DAC channel
 * @details Must called after every @p ht_audio_Play()
 */
void ht_audio_DisableCh(void);

/**
 * @brief Enable DAC Left Channel
 */
void ht_audio_LeftCh(void);

/**
 * @brief Enable DAC Right Channel
 */
void ht_audio_RightCh(void);

/**
 * @brief Generate tone for testing
 */
void ht_audio_TestTone(void);

/**
 * @brief Test Audio DAC Left then Right
 */
void ht_audio_TestBoth(void);

/**
 * @brief Test Audio DAC Left only
 */
void ht_audio_TestLeft(void);

/**
 * @brief Test Audio DAC Right only
 */
void ht_audio_TestRight(void);

/** @} */
