/*
 * CeptTable.h
 *
 *  Created on: 12.09.2013
 *      Author: braunefe
 */

#ifndef CEPTTABLE_H_
#define CEPTTABLE_H_

#include "tables-core.h"
#include "FeatureExtractor.h"
#include <vector>
#include <string>
#include <map>
#include <set>

struct CTableTranslation
{
  std::vector<float> m_scores;
};

typedef std::map<size_t, std::map<size_t, CTableTranslation> > DictionaryType;

class CeptTable
{
public:
  CeptTable(const std::string &fileName, PSD::IndexType *targetIndex);
  bool SrcExists(const std::string &phrase);

  // get all translations of source phrase, assumes that srcPhrase is known
  // (throws logic_error otherwise)
  const std::map<size_t, CTableTranslation> &GetTranslations(const std::string &srcCept);

private:
  DictionaryType m_ctable;
  PSD::IndexType *m_sourceIndex, *m_targetIndex;

  void AddCeptPair(const std::string &src, const std::string &tgt,
      const std::vector<float> &scores, const PSD::AlignmentType &align);
  std::vector<float> GetScores(const std::string &scoreStr);

  // add phrase to index (if it does not exist yet), return its ID
  size_t AddCept(const std::string &phrase, PSD::IndexType *index);

  size_t GetTgtPhraseID(const std::string &phrase, /* out */ bool *found);

};


#endif /* CEPTTABLE_H_ */