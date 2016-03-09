#pragma once

#include <string>
#include <algorithm>
#include "VWFeatureContext.h"
#include "moses/Util.h"

namespace Moses
{

class VWFeatureContextWindow : public VWFeatureContext
{
public:
  VWFeatureContextWindow(const std::string &line)
    : VWFeatureContext(line, DEFAULT_WINDOW_SIZE) {
    ReadParameters();

    // Call this last
    VWFeatureBase::UpdateRegister();
  }

  virtual void operator()(const Phrase &phrase
                          , Discriminative::Classifier &classifier
                          , Discriminative::FeatureVector &outFeatures) const {
    for (size_t i = 0; i < m_contextSize; i++)
      outFeatures.push_back(classifier.AddLabelIndependentFeature("tcwin^-" + SPrint(i + 1) + "^" + GetWord(phrase, i)));
  }

  virtual void SetParameter(const std::string& key, const std::string& value) {
    if (key == "size") {
      m_contextSize = Scan<size_t>(value);
    } else {
      VWFeatureContext::SetParameter(key, value);
    }
  }

private:
  static const int DEFAULT_WINDOW_SIZE = 1;
};

}
