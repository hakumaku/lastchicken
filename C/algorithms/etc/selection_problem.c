/*
 * Pseudocode
 * MINIMUM(A):
 *	min = A[1]
 *	for i = 2 to A.length
 *		if min > A[i]
 *			min = A[i]
 *	return min
 *
 * Pseudocode
 * RANDOMIZED_SELECT(A,p,r,i):
 *	if p == r
 *		return A[p]
 *	q = RANDOMIZED_PARTITION(A,p,r)
 *	k = q - p + 1
 *	if i == k
 *		return A[q]
 *	elseif i < k
 *		return RANDOMIZED_SELECT(A,p,q-1,i)
 *	else
 *		return RANDOMIZED_SELECT(A,q+1,r,i-k)
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TEST_VAL1	500

typedef struct {
	int min;
	int max;
}pair_t;

int minimum(int *arr, size_t len);
int maximum(int *arr, size_t len);
pair_t min_max(int *arr, size_t len);

int randomized_select(int *arr, size_t p, size_t r, size_t i);
size_t randomized_partition(int *arr, size_t p, size_t r);
size_t partition(int *arr, size_t p, size_t r);
size_t random(size_t a, size_t b);

int main(void)
{
	int test1[TEST_VAL1] = {
	929,373,432,1063,1043,217,1532,1994,214,39,1927,1755,1385,1742,780,1736,317,650,1079,1732
	,1248,849,416,469,75,1479,1084,165,317,1990,1838,1467,349,405,1573,572,1571,1845,744,378
	,1709,1429,665,747,1359,290,1359,120,954,1153,71,806,993,1080,418,1480,465,1945,1896,419
	,1784,87,693,1704,1690,1858,1818,1245,1163,54,28,1160,1248,206,386,1503,838,1466,1571,13
	,1365,1126,1196,890,1942,609,505,1699,1164,45,1775,1501,826,1953,539,1369,547,1284,1985,399
	,595,1255,1328,1359,513,222,23,1211,695,1907,1336,1999,1823,639,1489,450,908,1064,241,653
	,1206,164,792,1247,1929,1278,1541,125,1183,145,566,1894,703,1142,645,1132,843,1452,1943,1965
	,1753,920,136,1609,1388,531,266,1903,1682,1414,197,692,329,803,92,1589,1597,741,1844,140
	,252,799,325,219,1282,1708,456,1156,441,1472,1938,586,830,105,1718,1871,1882,794,615,526
	,387,906,224,132,1547,1634,545,258,1544,3,1297,1827,1725,945,46,347,710,152,190,1415
	,9,1760,1030,1944,51,284,689,78,1857,12,1304,1190,1214,341,1187,883,240,860,1440,1207
	,1692,476,1783,613,636,827,925,497,520,862,784,267,224,1720,1520,949,1802,1015,66,1662
	,1995,781,913,1203,1765,960,847,1714,1541,819,284,2000,849,301,191,521,1819,1887,1983,25
	,1906,1149,1465,1937,1059,1818,1509,657,1280,856,1413,592,1181,48,1894,1666,1645,627,1193,1834
	,634,1922,1804,1249,1869,1743,1762,1398,1945,61,187,1223,658,240,230,1125,1675,1179,1746,1076
	,1643,1684,1030,1356,1745,1457,1734,174,1427,1817,397,1935,1807,888,1569,1265,637,61,1343,1162
	,804,1366,1883,770,375,1844,1340,1198,1388,1508,819,1549,148,1747,1287,358,1728,1599,1441,131
	,949,1259,851,623,1105,248,1109,68,427,1435,648,1690,693,248,1207,996,113,461,1480,1226
	,1998,897,816,1820,666,1242,685,637,1952,396,992,1643,1993,271,939,1669,438,1901,130,1746
	,1862,510,423,1990,1271,709,1912,300,408,1632,369,19,1634,7,865,1792,64,1845,1724,902
	,1059,171,1002,149,1767,409,1856,1091,410,912,1225,1820,1253,1486,735,1380,1110,469,1391,352
	,33,534,1705,272,771,1769,523,655,588,882,1713,465,42,145,1184,1555,629,1185,326,388
	,1698,1246,91,1096,1845,1834,1297,1585,1619,653,779,993,1282,1184,978,1511,1045,210,427,1570
	,1598,1152,350,197,801,695,672,416,268,1152,1578,1325,338,1135,755,989,667,1731,222,1671
	,1332,471,1483,186,200,1204,577,737,69,1426,1136,1664,1856,1295,1075,346,1961,1537,1815,306
	};
	int order = 4;
	pair_t ret = {0 ,0};
	ret = min_max(test1, TEST_VAL1);
	printf("min:%d max:%d\n", minimum(test1, TEST_VAL1), maximum(test1, TEST_VAL1));
	printf("min:%d max:%d\n", ret.min, ret.max);
	printf("%dth min:%d\n", order, randomized_select(test1, 0, TEST_VAL1, order));

	return 0;
}

int minimum(int *arr, size_t len)
{
	int min = arr[0];
	for(size_t i = 1; i < len; i++)
	{
		if(min > arr[i])
			min = arr[i];
	}
	return min;
}
int maximum(int *arr, size_t len)
{
	int max = arr[0];
	for(size_t i = 1; i < len; i++)
	{
		if(max < arr[i])
			max = arr[i];
	}
	return max;
}

pair_t min_max(int *arr, size_t len)
{
	pair_t pair = {0, 0};
	size_t i = 1;
	int smallest = 0, largest = 0;

	/*	If odd, set both to the value of the first.	*/
	if(len & 1)
	{
		pair.min = arr[0];
		pair.max = arr[0];
	}
	/*	If even, perform 1 comparison.	*/
	else
	{
		largest = arr[0];
		smallest = largest ^ arr[1];
		if(largest < arr[1])
			largest = arr[1];
		smallest ^= largest;

		pair.min = smallest;
		pair.max = largest;
		i = 2;
	}

	while(i < len)
	{
		int v1 = arr[i], v2 = arr[i+1];
		largest =  v1;
		smallest = v1 ^ v2;

		/*	Determine arr[i] and arr[i+1]	*/
		if(largest < v2)
			largest = v2;
		smallest ^= largest;

		/*	min(pair.min, min(arr[i], arr[i+1]))	*/
		if(smallest < pair.min)
			pair.min = smallest;

		/*	max(pair.max, max(arr[i], arr[i+1]))	*/
		if(pair.max < largest)
			pair.max = largest;

		i += 2;
	}
	return pair;
}
/*
 * Returns the i th smallest element in the array.
 * i such that 1 <= i <= A.length
 */
int randomized_select(int *arr, size_t p, size_t r, size_t i)
{
	/*	[p, r)	*/
	if(p+1 == r)
		return arr[p];
	/*
	 * x1 < q < x2;
	 * any x1 in [p, q) such that x1 < q
	 * any x2 in (q, r) such that q < x2
	 */
	size_t q = randomized_partition(arr, p, r);
	/*
	 * k such that 1<= k <= A.length
	 * 'q' here can be ranged from 0 to A.length-1.
	 */
	size_t k = q - p + 1;
	if(i == k)
		return arr[q];
	else if(i < k)
		return randomized_select(arr, p, q, i);
	/*
	 * In the case where i > k,
	 * the i th smallest element of the entire array is
	 * the same as the (i-k) th smallest element of the subarray
	 * the size of which is k.
	 */
	else
		return randomized_select(arr, q+1, r, i-k);
}
size_t randomized_partition(int *arr, size_t p, size_t r)
{
	srand(time(NULL));
	size_t i = random(p, r);
	int temp = arr[r-1];
	arr[r-1] = arr[i];
	arr[i] = temp;

	return partition(arr, p, r);
}
size_t partition(int *arr, size_t p, size_t r)
{
	int temp = 0;
	int pivot = arr[r-1];
	size_t i = p, j = p;
	for(; j < r-1; j++)
	{
		if(arr[j] <= pivot)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}

	temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;

	return i;
}
size_t random(size_t a, size_t b)
{
	size_t ret = 0;
	size_t range = b - a;
	if(b < a)
		return 0;

	do {
		ret = rand();
	} while(ret >= (RAND_MAX - RAND_MAX % range));

	return (ret % range) + a;
}
