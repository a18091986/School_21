#include <gtest/gtest.h>
#include "Controller/controller.h"


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(SmartCalc, Validator_1){
    char str[] = "1+2+3-log(6)*sqrt(10)+ln(10)";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 0);
}


TEST(SmartCalc, Validator_2){
    char str[] = "1.123123+2mod4+(3*7)+sqrt(7)";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Validator_3){
    char str[] = "1+2mod4+3*(7+1)+acos(1/2)+5^2";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Validator_4){
    char str[] = "1+2mod4+3*(7+1)+asin(1/2)";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Validator_5){
    char str[] = "^1+2mod4+3*(7+1)+atan(1/2)";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_6){
    char str[] = "cos(1/2)+2mod4+3*(7+1)+sin(0)";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Validator_7){
    char str[] = "tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Validator_8){
    char str[] = "123456789+";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_9){
    char str[] = "1/2+aco(3)-lo(6)+l(8)-asi(5)+at(3)+tcos(213)^";
    s21::Controller ex;
    int status = ex.Validation(str);
    ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_10) {
  char str[] = "";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_11) {
  char str[] = "!1+4-f+d/";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_12) {
  char str[] = "1+4/";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_13) {
  char str[] = "!1+4-f+d/";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_14) {
  char str[] = "1+5-4*)";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_15) {
  char str[] = "1+((5-4)/410";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_16) {
  char str[] = "4mid2+(5-4)";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Validator_17) {
  char str[] = "1+";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, validation_18) {
  char str[] = "2^(2.1+1)-11mid2";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, validation_19) {
  char str[] = "2^(2.1+)-+11mod2";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, validation_20) {
  char str[] = "x.2-3-(2*3)";
  s21::Controller ex;
  int status = ex.Validation(str);
  ASSERT_EQ(status, 1);
}

TEST(SmartCalc, Result_1) {
  char str[] = "-cos(1)+3";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, 2.459697, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_2) {
  char str[] = "-0.1+0.2";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, 0.100000, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_3) {
  char str[] = "2^(2.1+1)-11mod2";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, 7.574187, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_4) {
  char str[] = "sin(0.5)-cos(1)+tan(0.5)+acos(0.5)-asin(1)-atan(1)";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, -0.823571, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_5) {
  char str[] = "sqrt(4.123456789)+3-1.12";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, 3.910629, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_6) {
  char str[] = "log(+10.2)-ln(10.2)";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, -1.313787, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_7) {
  char str[] = "log(+10.2)-ln(10.2)";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, -1.313787, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_8) {
  char str[] = "11+(-2)^5";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, -21.000000, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_9) {
  char str[] = "log(+10.2)+ln(10.2)";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, 3.330987, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_10) {
  char str[] = "sqrt(+4+1)+(-3+1)";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, 0.236068, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_11) {
  char str[] = "sqrt(3+1)-(-3+1)";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str);
    ASSERT_NEAR(res, 4.000000, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_12) {
  char str[] = "sin(x)";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str, 1.1);
    ASSERT_NEAR(res, 0.891207, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_13) {
  char str[] = "+5/0";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str, 1.1);
    ASSERT_TRUE(std::isinf(res));
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_14) {
  char str[] = "sqrt(-5.032)";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str, 1.1);
    ASSERT_TRUE(std::isnan(res));
  }
  ASSERT_EQ(status, 0);
}

TEST(SmartCalc, Result_15) {
  char str[] = "(+5*sqrt(4)-(-5+6))/3";
  s21::Controller ex;
  int status = ex.Validation(str);
  if (status == 0){
    double res = ex.Calculate(str, 1.1);
    ASSERT_NEAR(res, 3.000000, 0.0001);
  }
  ASSERT_EQ(status, 0);
}

