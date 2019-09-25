
#include <vector>
using namespace std;


///////////////////////////////////////////////////////////////
// see assignment description for explaination of this function
// make sure that the numbers in probs add up to approximately 1

int drawIndex(vector<double> &probs){

	int size = probs.size();

	double rNum = ( (double) (rand()%size) )/size;

	double sum = 0;
	
	// next 7 lines check that your input vector has sum approximately 1

	for ( int i = 0; i < size; i++ )
		sum = sum+probs[i];
	if ( sum < 0.95 || sum > 1.05)
	{ 
		printf("\nProbabilities  do not add to 1 (%f)", sum); 
		exit(0);
	}

	sum = 0;
	
	for ( int i = 0; i < size; i++ ){
		sum = sum + probs[i];
		if (sum > rNum ) return(i);
	}

	return(size-1);
}

/////////////////////////////////////////////////////////////////////
// Compute Levenshtein Distance
// Martin Ettl, 2012-10-05
 // Edit or levenshtein distance

size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2)
{
  const size_t m(s1.size());
  const size_t n(s2.size());
 
  if( m==0 ) return n;
  if( n==0 ) return m;
 
  size_t *costs = new size_t[n + 1];
 
  for( size_t k=0; k<=n; k++ ) costs[k] = k;
 
  size_t i = 0;
  for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
  {
    costs[0] = i+1;
    size_t corner = i;
 
    size_t j = 0;
    for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
    {
      size_t upper = costs[j+1];
      if( *it1 == *it2 )
      {
		  costs[j+1] = corner;
	  }
      else
	  {
		size_t t(upper<corner?upper:corner);
        costs[j+1] = (costs[j]<t?costs[j]:t)+1;
	  }
 
      corner = upper;
    }
  }
 
  size_t result = costs[n];
  delete [] costs;
 
  return result;
}
 
