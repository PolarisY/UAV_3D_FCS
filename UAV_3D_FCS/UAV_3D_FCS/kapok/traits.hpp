#pragma once
#include <memory>
#include <type_traits>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

namespace my_detail
{
	template<typename T>
	using decay_t = typename std::decay<T>::type;

	template<typename T> std::false_type static check_tuple_size(...);
	template<typename T> std::true_type static  check_tuple_size(decltype(std::tuple_size<T>::value)*);

	template<typename T>
	struct has_tuple_size : decltype(check_tuple_size<T>(nullptr))
	{
	};

	//has_begin_end
	template<typename T>
	struct has_begin_end
	{
	private:
		template<typename U> static auto Check(int) -> decltype(std::declval<U>().begin(), std::declval<U>().end(), std::true_type());
		template<typename U> static std::false_type Check(...);

	public:
		enum
		{
			value = std::is_same<decltype(Check<T>(0)), std::true_type>::value
		};
	};

#define HAS_XXX_TYPE(token)\
	template <typename T>struct has_##token{\
	private:\
	template<typename C> static std::true_type Check(typename C::token##*); \
		template<typename C> static std::false_type  Check(...);\
	public:\
		enum\
		{\
			value = std::is_same<decltype(Check<T>(0)), std::true_type>::value\
		};\
	};\

	HAS_XXX_TYPE(const_iterator)
	HAS_XXX_TYPE(mapped_type)

	template<typename T> struct is_poiner_extent : std::false_type{};

#define IS_SMART_POINTER(token)\
	template<typename T> struct is_poiner_extent<std::token##_ptr<T>> : std::true_type{}; \

	IS_SMART_POINTER(shared)
	IS_SMART_POINTER(unique)
	IS_SMART_POINTER(weak)
}

template<typename T>
struct is_string : std::integral_constant<bool, std::is_same<my_detail::decay_t<T>, std::string>::value>{};

template <typename T>
struct is_container : public std::integral_constant<bool, my_detail::has_const_iterator<my_detail::decay_t<T>>::value&&my_detail::has_begin_end<my_detail::decay_t<T>>::value>{};

template <typename T>
struct is_singlevalue_container : public std::integral_constant<bool, !std::is_array<my_detail::decay_t<T>>::value&&!my_detail::has_tuple_size<my_detail::decay_t<T>>::value && is_container<my_detail::decay_t<T>>::value&&!my_detail::has_mapped_type<my_detail::decay_t<T>>::value>{};

template <typename T>
struct is_map_container : public std::integral_constant<bool, is_container<my_detail::decay_t<T>>::value&&my_detail::has_mapped_type<my_detail::decay_t<T>>::value>{};

template<typename T>
struct is_normal_class : std::integral_constant<bool, std::is_class<my_detail::decay_t<T>>::value&&!is_string<T>::value>
{};

template<typename T>
struct is_basic_type : std::integral_constant<bool, std::is_arithmetic<my_detail::decay_t<T>>::value || is_string<T>::value>
{};

template<typename T>
struct is_smart_pointer : my_detail::is_poiner_extent<my_detail::decay_t<T>>{};

template<typename T>
struct is_pointer_ext : std::integral_constant<bool, std::is_pointer<my_detail::decay_t<T>>::value || is_smart_pointer<my_detail::decay_t<T>>::value>{};

template <typename T, template <typename...> class Template>
struct is_specialization_of : std::false_type {};

template <template <typename...> class Template, typename... Args>
struct is_specialization_of<Template<Args...>, Template> : std::true_type{};

#define IS_TEMPLATE_CLASS(token)\
template<typename T> struct is_##token : is_specialization_of<my_detail::decay_t<T>, std::token##>{}; \

IS_TEMPLATE_CLASS(tuple)
IS_TEMPLATE_CLASS(queue)
IS_TEMPLATE_CLASS(stack)
IS_TEMPLATE_CLASS(priority_queue)

template<typename T>
struct is_container_adapter : std::integral_constant<bool, is_queue<T>::value || is_stack<T>::value || is_priority_queue<T>::value>
{
};

template<typename T>
struct is_user_class : std::integral_constant<bool, is_normal_class<T>::value&&!is_container_adapter<T>::value&&!is_container<T>::value&&!is_tuple<T>::value>
{};
