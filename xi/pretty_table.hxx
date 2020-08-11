// vim:ts=3:sts=3:sw=3

#ifndef XI_PRETTY_TABLE_H_
#define XI_PRETTY_TABLE_H_

#include <list>
#include <map>
#include <string>
#include <vector>

namespace xi {

class PrettyTable {
   public :
      const uint32_t kMaxColumns = 32;

      enum Align {
         kLeft,
         kRight,
      };

   public :
      PrettyTable();

      // index는 0 base이다.
      void SetHead(uint32_t index, const std::string &value);
      void SetTail(uint32_t index, const std::string &value);
      void SetAlign(uint32_t index, Align value);
      void SetWidth(uint32_t index, uint32_t value);
      void SetMarginLeft(uint32_t value);
      void SetColumnValue(const uint32_t row_index, const uint32_t col_index, const char *value);
      void SetColumnValue(const uint32_t row_index, const uint32_t col_index, std::string value);
      void SetColumnValue(const uint32_t row_index, const uint32_t col_index, const int64_t value);
      void SetColumnValue(const uint32_t row_index, const uint32_t col_index, const uint64_t value);
      void AppendBody(const std::map<uint32_t, std::string> &row);
      void AppendBody(const std::list<std::string> &row);
      void AppendBody(const std::vector<std::string> &row);

      std::string Print();

   private :
      uint32_t CountColumns() const;
      uint32_t CountNewlines(const std::string &str) const;
      std::map<uint32_t, uint32_t> DetermineWidths(uint32_t columns) const;
      uint32_t DetermineWidth(const std::string &value) const;
      std::string ComposeLine(const std::map<uint32_t, uint32_t> &colwidths) const;
      std::list<std::string> ComposeRow(const std::map<uint32_t, uint32_t> &colwidths, std::map<uint32_t, std::string> &row) const;
      std::string PickLine(const uint32_t line, const std::string &value) const;
      Align GetAline(uint32_t index) const;
      void RebuildNewline(const std::map<uint32_t, uint32_t> &colwidths);
      std::string PrettyLine(const uint32_t width, const std::string &content);

   private :
      std::map<uint32_t, std::string> head_;
      std::map<uint32_t, std::string> tail_;
      std::map<uint32_t, Align> alignment_;
      std::map<uint32_t, uint32_t> colwidth_;
      std::list<std::map<uint32_t, std::string> > body_;

      char horizontal_;
      char vertical_;
      char corner_;
      std::string newline_;
      uint32_t margin_left_;
};

}

#endif
