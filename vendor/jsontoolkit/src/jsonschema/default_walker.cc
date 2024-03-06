#include <sourcemeta/jsontoolkit/jsonschema_walker.h>

auto sourcemeta::jsontoolkit::default_schema_walker(
    std::string_view keyword, const std::map<std::string, bool> &vocabularies)
    -> sourcemeta::jsontoolkit::SchemaWalkerStrategy {
#define WALK(vocabulary, _keyword, strategy)                                   \
  if (vocabularies.contains(vocabulary) && keyword == _keyword)                \
    return sourcemeta::jsontoolkit::SchemaWalkerStrategy::strategy;

#define HTTPS_BASE "https://json-schema.org/draft/"
  // 2020-12
  WALK(HTTPS_BASE "2020-12/vocab/core", "$defs", Members)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "items", Value)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "prefixItems", Elements)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "dependentSchemas", Members)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "properties", Members)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "patternProperties", Members)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "allOf", Elements)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "anyOf", Elements)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "oneOf", Elements)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "not", Value)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "if", Value)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "then", Value)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "else", Value)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "contains", Value)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "additionalProperties", Value)
  WALK(HTTPS_BASE "2020-12/vocab/applicator", "propertyNames", Value)
  WALK(HTTPS_BASE "2020-12/vocab/content", "contentSchema", Value)
  WALK(HTTPS_BASE "2020-12/vocab/unevaluated", "unevaluatedProperties", Value)
  WALK(HTTPS_BASE "2020-12/vocab/unevaluated", "unevaluatedItems", Value)

  // 2019-09
  WALK(HTTPS_BASE "2019-09/vocab/core", "$defs", Members)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "items", ValueOrElements)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "additionalItems", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "dependentSchemas", Members)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "unevaluatedProperties", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "unevaluatedItems", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "properties", Members)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "patternProperties", Members)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "allOf", Elements)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "anyOf", Elements)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "oneOf", Elements)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "not", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "if", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "then", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "else", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "contains", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "additionalProperties", Value)
  WALK(HTTPS_BASE "2019-09/vocab/applicator", "propertyNames", Value)
  WALK(HTTPS_BASE "2019-09/vocab/content", "contentSchema", Value)
  WALK(HTTPS_BASE "2019-09/vocab/hyper-schema", "hrefSchema", Value)
  WALK(HTTPS_BASE "2019-09/vocab/hyper-schema", "targetSchema", Value)
  WALK(HTTPS_BASE "2019-09/vocab/hyper-schema", "headerSchema", Value)
  WALK(HTTPS_BASE "2019-09/vocab/hyper-schema", "submissionSchema", Value)

#undef HTTPS_BASE

#define HTTP_BASE "http://json-schema.org/"
  // Draft7
  WALK(HTTP_BASE "draft-07/schema#", "definitions", Members)
  WALK(HTTP_BASE "draft-07/schema#", "dependencies", Members)
  WALK(HTTP_BASE "draft-07/schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-07/schema#", "additionalItems", Value)
  WALK(HTTP_BASE "draft-07/schema#", "properties", Members)
  WALK(HTTP_BASE "draft-07/schema#", "patternProperties", Members)
  WALK(HTTP_BASE "draft-07/schema#", "allOf", Elements)
  WALK(HTTP_BASE "draft-07/schema#", "anyOf", Elements)
  WALK(HTTP_BASE "draft-07/schema#", "oneOf", Elements)
  WALK(HTTP_BASE "draft-07/schema#", "not", Value)
  WALK(HTTP_BASE "draft-07/schema#", "if", Value)
  WALK(HTTP_BASE "draft-07/schema#", "then", Value)
  WALK(HTTP_BASE "draft-07/schema#", "else", Value)
  WALK(HTTP_BASE "draft-07/schema#", "contains", Value)
  WALK(HTTP_BASE "draft-07/schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-07/schema#", "propertyNames", Value)
  WALK(HTTP_BASE "draft-07/hyper-schema#", "hrefSchema", Value)
  WALK(HTTP_BASE "draft-07/hyper-schema#", "targetSchema", Value)
  WALK(HTTP_BASE "draft-07/hyper-schema#", "headerSchema", Value)
  WALK(HTTP_BASE "draft-07/hyper-schema#", "submissionSchema", Value)

  // Draft6
  WALK(HTTP_BASE "draft-06/schema#", "definitions", Members)
  WALK(HTTP_BASE "draft-06/schema#", "dependencies", Members)
  WALK(HTTP_BASE "draft-06/schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-06/schema#", "additionalItems", Value)
  WALK(HTTP_BASE "draft-06/schema#", "properties", Members)
  WALK(HTTP_BASE "draft-06/schema#", "patternProperties", Members)
  WALK(HTTP_BASE "draft-06/schema#", "allOf", Elements)
  WALK(HTTP_BASE "draft-06/schema#", "anyOf", Elements)
  WALK(HTTP_BASE "draft-06/schema#", "oneOf", Elements)
  WALK(HTTP_BASE "draft-06/schema#", "not", Value)
  WALK(HTTP_BASE "draft-06/schema#", "contains", Value)
  WALK(HTTP_BASE "draft-06/schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-06/schema#", "propertyNames", Value)
  WALK(HTTP_BASE "draft-06/hyper-schema#", "hrefSchema", Value)
  WALK(HTTP_BASE "draft-06/hyper-schema#", "targetSchema", Value)
  WALK(HTTP_BASE "draft-06/hyper-schema#", "submissionSchema", Value)

  // Draft4
  WALK(HTTP_BASE "draft-04/schema#", "definitions", Members)
  WALK(HTTP_BASE "draft-04/schema#", "dependencies", Members)
  WALK(HTTP_BASE "draft-04/schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-04/schema#", "additionalItems", Value)
  WALK(HTTP_BASE "draft-04/schema#", "properties", Members)
  WALK(HTTP_BASE "draft-04/schema#", "patternProperties", Members)
  WALK(HTTP_BASE "draft-04/schema#", "allOf", Elements)
  WALK(HTTP_BASE "draft-04/schema#", "anyOf", Elements)
  WALK(HTTP_BASE "draft-04/schema#", "oneOf", Elements)
  WALK(HTTP_BASE "draft-04/schema#", "not", Value)
  WALK(HTTP_BASE "draft-04/schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-04/hyper-schema#", "targetSchema", Value)
  WALK(HTTP_BASE "draft-04/hyper-schema#", "schema", Value)

  // Draft3
  WALK(HTTP_BASE "draft-03/schema#", "type", Elements)
  WALK(HTTP_BASE "draft-03/schema#", "dependencies", Members)
  WALK(HTTP_BASE "draft-03/schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-03/schema#", "additionalItems", Value)
  WALK(HTTP_BASE "draft-03/schema#", "properties", Members)
  WALK(HTTP_BASE "draft-03/schema#", "patternProperties", Members)
  WALK(HTTP_BASE "draft-03/schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-03/schema#", "disallow", Elements)
  WALK(HTTP_BASE "draft-03/schema#", "extends", ValueOrElements)
  WALK(HTTP_BASE "draft-03/hyper-schema#", "targetSchema", Value)

  // Draft2
  WALK(HTTP_BASE "draft-02/schema#", "type", Elements)
  WALK(HTTP_BASE "draft-02/schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-02/schema#", "properties", Members)
  WALK(HTTP_BASE "draft-02/schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-02/schema#", "extends", ValueOrElements)
  WALK(HTTP_BASE "draft-02/schema#", "requires", Value)
  WALK(HTTP_BASE "draft-02/hyper-schema#", "targetSchema", Value)
  WALK(HTTP_BASE "draft-02/hyper-schema#", "type", Elements)
  WALK(HTTP_BASE "draft-02/hyper-schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-02/hyper-schema#", "properties", Members)
  WALK(HTTP_BASE "draft-02/hyper-schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-02/hyper-schema#", "extends", ValueOrElements)
  WALK(HTTP_BASE "draft-02/hyper-schema#", "requires", Value)

  // Draft1
  WALK(HTTP_BASE "draft-01/schema#", "type", Elements)
  WALK(HTTP_BASE "draft-01/schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-01/schema#", "properties", Members)
  WALK(HTTP_BASE "draft-01/schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-01/schema#", "extends", ValueOrElements)
  WALK(HTTP_BASE "draft-01/schema#", "requires", Value)
  WALK(HTTP_BASE "draft-01/hyper-schema#", "type", Elements)
  WALK(HTTP_BASE "draft-01/hyper-schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-01/hyper-schema#", "properties", Members)
  WALK(HTTP_BASE "draft-01/hyper-schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-01/hyper-schema#", "extends", ValueOrElements)
  WALK(HTTP_BASE "draft-01/hyper-schema#", "requires", Value)

  // Draft0
  WALK(HTTP_BASE "draft-00/schema#", "type", Elements)
  WALK(HTTP_BASE "draft-00/schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-00/schema#", "properties", Members)
  WALK(HTTP_BASE "draft-00/schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-00/schema#", "extends", ValueOrElements)
  WALK(HTTP_BASE "draft-00/schema#", "requires", Value)
  WALK(HTTP_BASE "draft-00/hyper-schema#", "type", Elements)
  WALK(HTTP_BASE "draft-00/hyper-schema#", "items", ValueOrElements)
  WALK(HTTP_BASE "draft-00/hyper-schema#", "properties", Members)
  WALK(HTTP_BASE "draft-00/hyper-schema#", "additionalProperties", Value)
  WALK(HTTP_BASE "draft-00/hyper-schema#", "extends", ValueOrElements)
  WALK(HTTP_BASE "draft-00/hyper-schema#", "requires", Value)
#undef HTTP_BASE
#undef WALK
  return sourcemeta::jsontoolkit::SchemaWalkerStrategy::None;
}