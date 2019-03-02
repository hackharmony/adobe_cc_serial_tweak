#include <string>
#include <sstream>
#include <string_view>
#include <fstream>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

constexpr std::string_view default_filename {"/Library/Application Support/Adobe/Adobe Photoshop CC 2018/AMT/application.xml"};

int main(int argc, char* argv[]) {
  const std::string_view filename {argc > 1 ? argv[1] : default_filename};
  rapidxml::xml_document<char> doc;
  std::string straight_text{};
  {
    std::fstream f {default_filename.data(), std::ios::in};
    std::stringstream buf{};
    buf << f.rdbuf();
    straight_text = buf.str();
  }
  doc.parse<0>(straight_text.data());
  auto other_block = doc.first_node()->first_node("Other");
  if (other_block == nullptr) return 1;
  for (auto data_element = other_block->first_node(); data_element;
       data_element = data_element->next_sibling()) {
    if (std::string_view{data_element->first_attribute()->value()}  ==
        std::string_view{"TrialSerialNumber"}) {
      const std::string_view preexisting_trial_key {data_element->value()};
      std::string new_trial_key{};
      {
        std::stringstream buf;
        buf <<
          preexisting_trial_key.substr(0, preexisting_trial_key.length() - 5)
            << std::atoi(preexisting_trial_key.end() - 5) + 1;
        new_trial_key = buf.str();
      }
      constexpr std::string_view data_node_name {"Data"};
      auto new_node = doc.allocate_node(rapidxml::node_element, data_node_name.data(), new_trial_key.c_str(), data_node_name.length());
      auto new_attr = doc.allocate_attribute("key", "TrialSerialNumber");
      new_node->append_attribute(new_attr);
      other_block->append_node(new_node);
      other_block->remove_node(data_element);
      // RapidXML doesn't re-serialize with the first line, so we have to manually retrieve it
      const auto first_line =
        std::string_view{&straight_text[0],
                         straight_text.find('\n', 0)};
      // Write the new XML to file
      std::fstream f {filename.data(), std::ios::out | std::ios::trunc};
      f << first_line << '\n' << doc << '\n';
      doc.clear();
      break;
    }
  }
  return 0;
}
