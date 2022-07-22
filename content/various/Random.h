/**
 * Author: Cube219
 * Date: 2022-07-22
 * Description:
 */
#pragma once

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distribution(0, INT_MAX);
int getRandom() { return distribution(rng); }
