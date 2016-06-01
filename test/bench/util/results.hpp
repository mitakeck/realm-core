/*************************************************************************
 *
 * REALM CONFIDENTIAL
 * __________________
 *
 *  [2011] - [2015] Realm Inc
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Realm Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Realm Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Realm Incorporated.
 *
 **************************************************************************/
#ifndef REALM_TEST_UTIL_RESULTS_HPP
#define REALM_TEST_UTIL_RESULTS_HPP

#include <vector>
#include <map>
#include <string>

namespace realm {
namespace test_util {


class Results {
public:
    Results(int max_lead_text_width,
            const char* results_file_stem = "results");
    ~Results();

    enum ChangeType {
        change_Percent,
        change_DropFactor,
        change_RiseFactor
    };

    /// Use submit_single() when you know there is only going to be a single
    /// datapoint.
    void submit_single(const char* ident, const char* lead_text,
                       double seconds, ChangeType = change_Percent);

    /// Use submit() when there are multiple data points, and call finish()
    /// when you are done.
    void submit(const char* ident, double seconds);
    void finish(const std::string& ident, const std::string& lead_text,
                ChangeType = change_Percent);

private:
    int m_max_lead_text_width;
    std::string m_results_file_stem;

    struct Result {
        Result();
        double min;
        double max;
        double total;
        double stddev;
        double median;
        double mode;
        size_t rep;

        double avg() const;
    };

    struct Measurement {
        std::vector<double> samples;

        Result finish() const;
    };

    typedef std::map<std::string, Measurement> Measurements;
    Measurements m_measurements;
    typedef std::map<std::string, Result> BaselineResults;
    BaselineResults m_baseline_results;

    void try_load_baseline_results();
    void save_results();
};


// Implementation:

inline Results::Results(int max_lead_text_width,
                        const char* results_file_stem):
                            m_max_lead_text_width(max_lead_text_width),
                            m_results_file_stem(results_file_stem)
{
    try_load_baseline_results();
}

inline Results::~Results()
{
    if (!m_measurements.empty())
        save_results();
}


} // namespace test_util
} // namespace realm

#endif // REALM_TEST_UTIL_RESULTS_HPP