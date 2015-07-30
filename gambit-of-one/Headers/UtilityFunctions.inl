template <typename T>
std::string toString(const T& value)
{
	std::stringstream s;
	s << value;
	return s.str();
}