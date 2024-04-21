#include "Cell.h"

Cell::Cell()
{}

Cell::Cell(const Cell& rhv)
{
   val = rhv.val;
}

Cell::Cell(Cell&& rhv)
{
   val = rhv.val;
   rhv.val = '\0';
}  

Cell::Cell(int num)
{
   val = std::to_string(num);
}

Cell::Cell(double num)
{
   val = std::to_string(num);
}

Cell::Cell(char ch)
{
   val = "'";
   val += {ch};
   val += "'";
}

Cell::Cell(bool num)
{
   if(num)
   {
      val = "true";
   }
   else{
      val = "false";
   }
}

Cell::Cell(std::string str)
{
   val = '"' + str;
   val += '"';
}

Cell::Cell(const std::vector<int>& vec)
{
   val = '{';
   for(auto it = vec.begin(); it != vec.end(); ++it)
   {
      val += std::to_string(*it) + ',';
   }
   val.pop_back();
   val += '}';
}

std::string Cell::GetVal() const
{
   return val;
}

//OPERATOR=

const Cell& Cell::operator=(const Cell& rhv)
{  
   if(this != &rhv)
   {
      val = rhv.val;
   }
   return *this;
}

const Cell& Cell::operator=(Cell&& rhv)
{
   val = rhv.val;
   rhv.val = '\0';

   return *this;
}

const Cell& Cell::operator=(int rhv)
{
   val = std::to_string(rhv);
   return *this;
}

const Cell& Cell::operator=(double rhv)
{
   val = std::to_string(rhv);
   return *this;
}

const Cell& Cell::operator=(char rhv)
{ 
   val = "'";
   val += {rhv};
   val += "'";
   return *this;
}

const Cell& Cell::operator=(bool rhv)
{
   if(rhv)
   {
      val = "true";
   }
   else{
      val = "false";
   }
   return *this;
}
const Cell& Cell::operator=(std::string rhv)
{
   val = '"' + rhv;
   val += '"';
   return *this;
}


const Cell& Cell::operator=(const std::vector<int>& rhv)
{
   val = '{';
   for(auto it = rhv.begin(); it != rhv.end(); ++it)
   {
      val += std::to_string(*it) + ',';
   }
   val.pop_back();
   val += '}';
   return *this;
}

//OPERATOR CAST
Cell::operator int()
{
   int result = 0;
   std::string tmp = val;

   if(tmp[0] == '"' || tmp[0] == '{' || tmp[0] == '\'')
      val.erase(0,1);

   for (char c : tmp)
   {
      if (isdigit(c)) 
      {
         result = result * 10 + (c - '0');
      } 
      else
      {
      return result;   
      }
   }
   return result;
}



Cell::operator double()
{
   double result = 0;
   int count = 0;
   int j = 0;
   std::string tmp = val;

   if(tmp[0] == '"' || tmp[0] == '{' || tmp[0] == '\'')
      tmp.erase(0,1);

   for (char c : tmp)
   {
      if (isdigit(c)) 
      {
         result = result * 10 + (c - '0');
         if(j  != 0)
            ++count;
      }      
      else if('.' == c)
      {
         ++j;
         break;
      }
      else 
      {
         for(int i = 0; i < count; ++i)
         {
            result /= 10;
         }
         return result;
      }
   }
   return result;
}


Cell::operator char()
{
   if(val == "false" || val == "true" ||  val.size() == 1)
   {
      return val[0];
   }
   return val[1];
}

Cell::operator bool()
{
   if(val == "false" || val[0] == '0')
   {
      return false;
   }
  
   if(val[0] != '{' && val[0] != '"' && val[0] != '\'')
   {
      return val.size();
   }

   return !(val[1] != '\0' ^ val[1] != '0');
}


Cell::operator std::string()
{
   std::string tmp = val;
   if(val[0] == '"') {
   tmp.erase(0,1);
   tmp.erase(val.size() - 1 , 1);
   }
   return tmp;
}


Cell::operator std::vector<int>()
{

   std::vector<int> arr;
   std::string tmp = val;
   if(val[0] == '{' && val[val.size() - 1] == '}')
   {
      tmp.erase(0,1);
      tmp.erase(val.size() - 1, 1);
      std::string i;
      std::stringstream ss(tmp);

      while(std::getline(ss , i , ',') )
      {
         arr.push_back(std::stoi(i));
      
      }
   }
   return arr;
}
//OPERATOR == >> << !=

bool operator==(const Cell& lhv, const Cell& rhv)
{
   return lhv.GetVal() == rhv.GetVal();
}
bool operator!=(const Cell& lhv, const Cell& rhv)
{
   return !(lhv == rhv);
}


std::ostream& operator<<(std::ostream& out, const Cell& ob)
{
   out << ob.GetVal();
   return out;
}

std::istream& operator>>(std::istream& in, Cell& ob)
{
  std::string input;
   in >> input;
   if(isdigit(input[0])) {
   int i = 0;
   int j = 0;
   int k = 0;
   while(k < input.size()) {
      if( j == 0 && input[k] == '.') {
         ++j;
         ++i;
         continue;
      }
      if(isdigit(input[k])) { ++i;}
      ++k;
   }
   if(j == 0 && i == input.size()) {
   ob = std::stoi(input);
   return in;
   }
   if(i  == input.size() && j != 0)
   {
   double d = std::stod(input);
   ob = d;
   return in;
   }
   }
   if(input.size() == 1 && (!isdigit(input[0]))) {
      ob = input[0];
      return in;
   }
   if(input == "true") { ob = (bool)1; return in;}
   if(input == "false") { ob = (bool)0; return in;}

   ob = input;
   return in;
}
/*
int main()
{
   Cell o2('0');
   std::cout << o2.GetVal();
   
   std::string str{"0"};
   Cell o6(str);
   std::cout << o6.GetVal();

   bool a = bool(o6);
   if(a)
   {
      std::cout << "   TRUE A \n ";
   }
   else{std::cout << " False a\n ";}
   
   std::vector<int> ar = {5, 45, 654, 1};
   Cell o5(ar);
   std::vector<int> arr = std::vector<int>(o5);
   for(int i = 0 ; i < arr.size(); ++i)
   {
      std::cout << "  "<< arr[i];
   }


   std::cin >> o2;
   int ad = (int)o2;
   o2 = ad;
   std::cout << o2;
   Cell o3(8);
   int ac = (int)o3;
//   o3 = ac;
   std::cout << ac;



}
*/
