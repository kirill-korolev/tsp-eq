#pragma once

#include "CsvParser.h"
#include "TSP.Set.Feature.h"

#include <vector>
#include <array>
#include <exception>
#include <string>
#include <cctype>
#include <cmath>

using csv::Row;
using csv::Parser;

namespace TSPNeuralNet { namespace Set {

	typedef unsigned int uint;

	namespace Utils {

		static inline void ltrim(std::string &s) {
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
				return !std::isspace(ch);
			}));
		}

		static inline void rtrim(std::string &s) {
			s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
				return !std::isspace(ch);
			}).base(), s.end());
		}

		static inline void trim(std::string &s) {
			ltrim(s);
			rtrim(s);
		}

	}

	typedef std::vector<double> TspRow;
	typedef std::vector<TspRow> TspSet;

	template <typename T, size_t Index = 0, size_t Size = 0>
	auto makeSet(const char* fileName)->TspSet;

	template <size_t Index = 0, size_t Size = 0, typename... Features>
	auto makeSet(const char* fileName, Features... features)->TspSet;

	TspSet getLastRows(const TspSet& set, uint index, size_t n);
	std::vector<TspSet> divide(const TspSet& set, size_t size);

}}

namespace TSPNeuralNet { namespace Set {

		template <typename FeatureType>
		inline auto readRow(Row r, std::vector<int>& indexes, FeatureType f) ->
			std::vector<double>
		{
			std::vector<double> t;
			auto value = r.getValue<typename FeatureType::f_type>(indexes.front());
			t.push_back(value);
			return t;
		}

		template <typename FeatureType, typename... Features>
		inline std::vector<double> readRow(Row r, std::vector<int>& indexes, FeatureType f, Features... features)
		{
			auto t = read_row(r, indexes, f);
			auto other = read_row(r, indexes, features...);
			t.insert(t.end(), other.begin(), other.end());
			return t;
		}

		template <typename T>
		inline std::vector<double> readRow(Row r)
		{
			std::vector<double> result;

			for (int i = 0; i < r.size(); ++i) {
				auto value = r.getValue<T>(i);
				result.push_back(value);
			}

			return result;
		}

		template <typename FeatureType> 
		inline void findFeatures(std::vector<int>& indexes, const std::vector<std::string>& header, const TspFeature<FeatureType>& f) {
			for (int i = 0; i < header.size(); ++i) {
				auto s = header.at(i);
				utils::trim(s);
				if (s.compare(f.getTitle()) == 0) {
					indexes.push_back(i);
					return;
				}
			}
			throw std::invalid_argument("No such feature in a dataset");
		}

		template <typename FeatureType, typename... Features>
		inline void findFeatures(std::vector<int>& indexes, const std::vector<std::string>& header, const TspFeature<FeatureType>& f, Features... features) {
			findFeatures(indexes, header, f);
			findFeatures(indexes, header, features...);
		}


		template <typename T, size_t Index, size_t Size>
		inline auto makeSet(const char* fileName) -> TspSet {
			Parser parser(fileName);
			std::vector<std::vector<double>> result;

			for (int i = Index; i < (Size == 0 ? parser.rowCount() : Index + Size); ++i)
			{
				auto row = readRow<T>(parser.getRow(i));
				result.push_back(std::move(row));
			}

			return result;
		}

		template <size_t Index, size_t Size, typename... Features>
		inline auto makeSet(const char* fileName, Features... features) ->
			TspSet
		{
			Parser parser(fileName);
			auto header = parser.getHeader();
			if (header.size() == 0) throw std::length_error("There is no header in a dataset");
			std::vector<int> indexes;
			findFeatures(indexes, header, features...);

			std::vector<std::vector<double>> result;

			for (int i = Index; i < (Size == 0 ? parser.rowCount() : Index + Size); ++i)
			{
				auto row = readRow(parser.getRow(i), indexes, features...);
				result.push_back(std::move(row));
			}

			return result;
		}


		inline TspSet getLastRows(const TspSet& set, uint index, size_t n)
		{
			try {
				TspSet s(set.begin() + index - n, set.begin() + index);
				return s;
			}
			catch (std::exception& e)
			{
				throw e;
			}
		}

		inline std::vector<TspSet> divide(const TspSet& set, size_t size)
		{
			size_t set_size = set.size();
			size_t pieces = std::ceil((double)set_size / size);

			std::vector<TspSet> sets;

			for (int i = 0; i < pieces; ++i)
			{
				TspSet::const_iterator p = set.begin() + (i + 1) * size;
				TspSet subset(set.begin() + i * size, p < set.end() ? p : set.end());
				sets.push_back(std::move(subset));
			}

			return sets;
		}

}}