#ifndef UTILS_H_
#define UTILS_H_


#define U__BIT_SET(reg,bit) ((reg) |=  (1u << (bit)))
#define U__BIT_CLR(reg,bit) ((reg) &= ~(1u << (bit)))
#define U__BIT_GET(reg,bit) (((reg) >> (bit)) & 0x01u)

#define U__INIT_VALUE_FLOAT (0.0f)
#define U__INIT_VALUE_UINT    (0u)
#define U__INIT_VALUE_SINT    (0)

#define U__FALSE    (0u)
#define U__TRUE     (1u)

#define U__INPUT    (0u)
#define U__OUTPUT   (1u)

#define U__LOW      (0u)
#define U__HIGH     (1u)

#define U__DISABLE  (0u)
#define U__ENABLE   (1u)

#define U__PI       ((float32) (3.141592654f))

#define U__DEG_TO_RAD(degree)   ((float32)degree * (U__PI / 180.0f))
#define U__RAD_TO_DEG(radian)   ((float32)radian * (180.0f / U__PI))

#define U__SIND(degree)             (sin(U__DEG_TO_RAD(degree)))
#define U__COSD(degree)             (cos(U__DEG_TO_RAD(degree)))
#define U__NORMALIZE(raw_degree)    (raw_degree - (floor(raw_degree / 360.0f) * 360.0f))


#endif /* UTILS_H_ */
