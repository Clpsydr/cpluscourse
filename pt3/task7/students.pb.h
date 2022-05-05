// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: students.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_students_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_students_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3013000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3013000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_students_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_students_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_students_2eproto;
class FullName;
class FullNameDefaultTypeInternal;
extern FullNameDefaultTypeInternal _FullName_default_instance_;
class Student;
class StudentDefaultTypeInternal;
extern StudentDefaultTypeInternal _Student_default_instance_;
class StudentsGroup;
class StudentsGroupDefaultTypeInternal;
extern StudentsGroupDefaultTypeInternal _StudentsGroup_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::FullName* Arena::CreateMaybeMessage<::FullName>(Arena*);
template<> ::Student* Arena::CreateMaybeMessage<::Student>(Arena*);
template<> ::StudentsGroup* Arena::CreateMaybeMessage<::StudentsGroup>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class FullName PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:FullName) */ {
 public:
  inline FullName() : FullName(nullptr) {}
  virtual ~FullName();

  FullName(const FullName& from);
  FullName(FullName&& from) noexcept
    : FullName() {
    *this = ::std::move(from);
  }

  inline FullName& operator=(const FullName& from) {
    CopyFrom(from);
    return *this;
  }
  inline FullName& operator=(FullName&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const FullName& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const FullName* internal_default_instance() {
    return reinterpret_cast<const FullName*>(
               &_FullName_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(FullName& a, FullName& b) {
    a.Swap(&b);
  }
  inline void Swap(FullName* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(FullName* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline FullName* New() const final {
    return CreateMaybeMessage<FullName>(nullptr);
  }

  FullName* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<FullName>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const FullName& from);
  void MergeFrom(const FullName& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(FullName* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "FullName";
  }
  protected:
  explicit FullName(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_students_2eproto);
    return ::descriptor_table_students_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSurnameFieldNumber = 1,
    kNameFieldNumber = 2,
    kPatronymicFieldNumber = 3,
  };
  // string Surname = 1;
  void clear_surname();
  const std::string& surname() const;
  void set_surname(const std::string& value);
  void set_surname(std::string&& value);
  void set_surname(const char* value);
  void set_surname(const char* value, size_t size);
  std::string* mutable_surname();
  std::string* release_surname();
  void set_allocated_surname(std::string* surname);
  private:
  const std::string& _internal_surname() const;
  void _internal_set_surname(const std::string& value);
  std::string* _internal_mutable_surname();
  public:

  // string Name = 2;
  void clear_name();
  const std::string& name() const;
  void set_name(const std::string& value);
  void set_name(std::string&& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  std::string* mutable_name();
  std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // string Patronymic = 3;
  bool has_patronymic() const;
  private:
  bool _internal_has_patronymic() const;
  public:
  void clear_patronymic();
  const std::string& patronymic() const;
  void set_patronymic(const std::string& value);
  void set_patronymic(std::string&& value);
  void set_patronymic(const char* value);
  void set_patronymic(const char* value, size_t size);
  std::string* mutable_patronymic();
  std::string* release_patronymic();
  void set_allocated_patronymic(std::string* patronymic);
  private:
  const std::string& _internal_patronymic() const;
  void _internal_set_patronymic(const std::string& value);
  std::string* _internal_mutable_patronymic();
  public:

  // @@protoc_insertion_point(class_scope:FullName)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr surname_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr patronymic_;
  friend struct ::TableStruct_students_2eproto;
};
// -------------------------------------------------------------------

class Student PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Student) */ {
 public:
  inline Student() : Student(nullptr) {}
  virtual ~Student();

  Student(const Student& from);
  Student(Student&& from) noexcept
    : Student() {
    *this = ::std::move(from);
  }

  inline Student& operator=(const Student& from) {
    CopyFrom(from);
    return *this;
  }
  inline Student& operator=(Student&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Student& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Student* internal_default_instance() {
    return reinterpret_cast<const Student*>(
               &_Student_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Student& a, Student& b) {
    a.Swap(&b);
  }
  inline void Swap(Student* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Student* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Student* New() const final {
    return CreateMaybeMessage<Student>(nullptr);
  }

  Student* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Student>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Student& from);
  void MergeFrom(const Student& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Student* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Student";
  }
  protected:
  explicit Student(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_students_2eproto);
    return ::descriptor_table_students_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kGradesFieldNumber = 2,
    kFioFieldNumber = 1,
    kAvggradeFieldNumber = 3,
  };
  // repeated int32 Grades = 2;
  int grades_size() const;
  private:
  int _internal_grades_size() const;
  public:
  void clear_grades();
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_grades(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      _internal_grades() const;
  void _internal_add_grades(::PROTOBUF_NAMESPACE_ID::int32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      _internal_mutable_grades();
  public:
  ::PROTOBUF_NAMESPACE_ID::int32 grades(int index) const;
  void set_grades(int index, ::PROTOBUF_NAMESPACE_ID::int32 value);
  void add_grades(::PROTOBUF_NAMESPACE_ID::int32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      grades() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      mutable_grades();

  // .FullName Fio = 1;
  bool has_fio() const;
  private:
  bool _internal_has_fio() const;
  public:
  void clear_fio();
  const ::FullName& fio() const;
  ::FullName* release_fio();
  ::FullName* mutable_fio();
  void set_allocated_fio(::FullName* fio);
  private:
  const ::FullName& _internal_fio() const;
  ::FullName* _internal_mutable_fio();
  public:
  void unsafe_arena_set_allocated_fio(
      ::FullName* fio);
  ::FullName* unsafe_arena_release_fio();

  // int32 Avggrade = 3;
  void clear_avggrade();
  ::PROTOBUF_NAMESPACE_ID::int32 avggrade() const;
  void set_avggrade(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_avggrade() const;
  void _internal_set_avggrade(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:Student)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 > grades_;
  mutable std::atomic<int> _grades_cached_byte_size_;
  ::FullName* fio_;
  ::PROTOBUF_NAMESPACE_ID::int32 avggrade_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_students_2eproto;
};
// -------------------------------------------------------------------

class StudentsGroup PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:StudentsGroup) */ {
 public:
  inline StudentsGroup() : StudentsGroup(nullptr) {}
  virtual ~StudentsGroup();

  StudentsGroup(const StudentsGroup& from);
  StudentsGroup(StudentsGroup&& from) noexcept
    : StudentsGroup() {
    *this = ::std::move(from);
  }

  inline StudentsGroup& operator=(const StudentsGroup& from) {
    CopyFrom(from);
    return *this;
  }
  inline StudentsGroup& operator=(StudentsGroup&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const StudentsGroup& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const StudentsGroup* internal_default_instance() {
    return reinterpret_cast<const StudentsGroup*>(
               &_StudentsGroup_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(StudentsGroup& a, StudentsGroup& b) {
    a.Swap(&b);
  }
  inline void Swap(StudentsGroup* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(StudentsGroup* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline StudentsGroup* New() const final {
    return CreateMaybeMessage<StudentsGroup>(nullptr);
  }

  StudentsGroup* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<StudentsGroup>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const StudentsGroup& from);
  void MergeFrom(const StudentsGroup& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(StudentsGroup* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "StudentsGroup";
  }
  protected:
  explicit StudentsGroup(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_students_2eproto);
    return ::descriptor_table_students_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kStudentsFieldNumber = 1,
  };
  // repeated .Student students = 1;
  int students_size() const;
  private:
  int _internal_students_size() const;
  public:
  void clear_students();
  ::Student* mutable_students(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Student >*
      mutable_students();
  private:
  const ::Student& _internal_students(int index) const;
  ::Student* _internal_add_students();
  public:
  const ::Student& students(int index) const;
  ::Student* add_students();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Student >&
      students() const;

  // @@protoc_insertion_point(class_scope:StudentsGroup)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Student > students_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_students_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// FullName

// string Surname = 1;
inline void FullName::clear_surname() {
  surname_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline const std::string& FullName::surname() const {
  // @@protoc_insertion_point(field_get:FullName.Surname)
  return _internal_surname();
}
inline void FullName::set_surname(const std::string& value) {
  _internal_set_surname(value);
  // @@protoc_insertion_point(field_set:FullName.Surname)
}
inline std::string* FullName::mutable_surname() {
  // @@protoc_insertion_point(field_mutable:FullName.Surname)
  return _internal_mutable_surname();
}
inline const std::string& FullName::_internal_surname() const {
  return surname_.Get();
}
inline void FullName::_internal_set_surname(const std::string& value) {
  
  surname_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void FullName::set_surname(std::string&& value) {
  
  surname_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:FullName.Surname)
}
inline void FullName::set_surname(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  surname_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:FullName.Surname)
}
inline void FullName::set_surname(const char* value,
    size_t size) {
  
  surname_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:FullName.Surname)
}
inline std::string* FullName::_internal_mutable_surname() {
  
  return surname_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* FullName::release_surname() {
  // @@protoc_insertion_point(field_release:FullName.Surname)
  return surname_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void FullName::set_allocated_surname(std::string* surname) {
  if (surname != nullptr) {
    
  } else {
    
  }
  surname_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), surname,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:FullName.Surname)
}

// string Name = 2;
inline void FullName::clear_name() {
  name_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline const std::string& FullName::name() const {
  // @@protoc_insertion_point(field_get:FullName.Name)
  return _internal_name();
}
inline void FullName::set_name(const std::string& value) {
  _internal_set_name(value);
  // @@protoc_insertion_point(field_set:FullName.Name)
}
inline std::string* FullName::mutable_name() {
  // @@protoc_insertion_point(field_mutable:FullName.Name)
  return _internal_mutable_name();
}
inline const std::string& FullName::_internal_name() const {
  return name_.Get();
}
inline void FullName::_internal_set_name(const std::string& value) {
  
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void FullName::set_name(std::string&& value) {
  
  name_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:FullName.Name)
}
inline void FullName::set_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:FullName.Name)
}
inline void FullName::set_name(const char* value,
    size_t size) {
  
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:FullName.Name)
}
inline std::string* FullName::_internal_mutable_name() {
  
  return name_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* FullName::release_name() {
  // @@protoc_insertion_point(field_release:FullName.Name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void FullName::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:FullName.Name)
}

// string Patronymic = 3;
inline bool FullName::_internal_has_patronymic() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool FullName::has_patronymic() const {
  return _internal_has_patronymic();
}
inline void FullName::clear_patronymic() {
  patronymic_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& FullName::patronymic() const {
  // @@protoc_insertion_point(field_get:FullName.Patronymic)
  return _internal_patronymic();
}
inline void FullName::set_patronymic(const std::string& value) {
  _internal_set_patronymic(value);
  // @@protoc_insertion_point(field_set:FullName.Patronymic)
}
inline std::string* FullName::mutable_patronymic() {
  // @@protoc_insertion_point(field_mutable:FullName.Patronymic)
  return _internal_mutable_patronymic();
}
inline const std::string& FullName::_internal_patronymic() const {
  return patronymic_.Get();
}
inline void FullName::_internal_set_patronymic(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  patronymic_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void FullName::set_patronymic(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  patronymic_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:FullName.Patronymic)
}
inline void FullName::set_patronymic(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  patronymic_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:FullName.Patronymic)
}
inline void FullName::set_patronymic(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000001u;
  patronymic_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:FullName.Patronymic)
}
inline std::string* FullName::_internal_mutable_patronymic() {
  _has_bits_[0] |= 0x00000001u;
  return patronymic_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* FullName::release_patronymic() {
  // @@protoc_insertion_point(field_release:FullName.Patronymic)
  if (!_internal_has_patronymic()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return patronymic_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void FullName::set_allocated_patronymic(std::string* patronymic) {
  if (patronymic != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  patronymic_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), patronymic,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:FullName.Patronymic)
}

// -------------------------------------------------------------------

// Student

// .FullName Fio = 1;
inline bool Student::_internal_has_fio() const {
  return this != internal_default_instance() && fio_ != nullptr;
}
inline bool Student::has_fio() const {
  return _internal_has_fio();
}
inline void Student::clear_fio() {
  if (GetArena() == nullptr && fio_ != nullptr) {
    delete fio_;
  }
  fio_ = nullptr;
}
inline const ::FullName& Student::_internal_fio() const {
  const ::FullName* p = fio_;
  return p != nullptr ? *p : *reinterpret_cast<const ::FullName*>(
      &::_FullName_default_instance_);
}
inline const ::FullName& Student::fio() const {
  // @@protoc_insertion_point(field_get:Student.Fio)
  return _internal_fio();
}
inline void Student::unsafe_arena_set_allocated_fio(
    ::FullName* fio) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(fio_);
  }
  fio_ = fio;
  if (fio) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:Student.Fio)
}
inline ::FullName* Student::release_fio() {
  
  ::FullName* temp = fio_;
  fio_ = nullptr;
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::FullName* Student::unsafe_arena_release_fio() {
  // @@protoc_insertion_point(field_release:Student.Fio)
  
  ::FullName* temp = fio_;
  fio_ = nullptr;
  return temp;
}
inline ::FullName* Student::_internal_mutable_fio() {
  
  if (fio_ == nullptr) {
    auto* p = CreateMaybeMessage<::FullName>(GetArena());
    fio_ = p;
  }
  return fio_;
}
inline ::FullName* Student::mutable_fio() {
  // @@protoc_insertion_point(field_mutable:Student.Fio)
  return _internal_mutable_fio();
}
inline void Student::set_allocated_fio(::FullName* fio) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete fio_;
  }
  if (fio) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::GetArena(fio);
    if (message_arena != submessage_arena) {
      fio = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, fio, submessage_arena);
    }
    
  } else {
    
  }
  fio_ = fio;
  // @@protoc_insertion_point(field_set_allocated:Student.Fio)
}

// repeated int32 Grades = 2;
inline int Student::_internal_grades_size() const {
  return grades_.size();
}
inline int Student::grades_size() const {
  return _internal_grades_size();
}
inline void Student::clear_grades() {
  grades_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Student::_internal_grades(int index) const {
  return grades_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Student::grades(int index) const {
  // @@protoc_insertion_point(field_get:Student.Grades)
  return _internal_grades(index);
}
inline void Student::set_grades(int index, ::PROTOBUF_NAMESPACE_ID::int32 value) {
  grades_.Set(index, value);
  // @@protoc_insertion_point(field_set:Student.Grades)
}
inline void Student::_internal_add_grades(::PROTOBUF_NAMESPACE_ID::int32 value) {
  grades_.Add(value);
}
inline void Student::add_grades(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_add_grades(value);
  // @@protoc_insertion_point(field_add:Student.Grades)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
Student::_internal_grades() const {
  return grades_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
Student::grades() const {
  // @@protoc_insertion_point(field_list:Student.Grades)
  return _internal_grades();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
Student::_internal_mutable_grades() {
  return &grades_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
Student::mutable_grades() {
  // @@protoc_insertion_point(field_mutable_list:Student.Grades)
  return _internal_mutable_grades();
}

// int32 Avggrade = 3;
inline void Student::clear_avggrade() {
  avggrade_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Student::_internal_avggrade() const {
  return avggrade_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Student::avggrade() const {
  // @@protoc_insertion_point(field_get:Student.Avggrade)
  return _internal_avggrade();
}
inline void Student::_internal_set_avggrade(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  avggrade_ = value;
}
inline void Student::set_avggrade(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_avggrade(value);
  // @@protoc_insertion_point(field_set:Student.Avggrade)
}

// -------------------------------------------------------------------

// StudentsGroup

// repeated .Student students = 1;
inline int StudentsGroup::_internal_students_size() const {
  return students_.size();
}
inline int StudentsGroup::students_size() const {
  return _internal_students_size();
}
inline void StudentsGroup::clear_students() {
  students_.Clear();
}
inline ::Student* StudentsGroup::mutable_students(int index) {
  // @@protoc_insertion_point(field_mutable:StudentsGroup.students)
  return students_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Student >*
StudentsGroup::mutable_students() {
  // @@protoc_insertion_point(field_mutable_list:StudentsGroup.students)
  return &students_;
}
inline const ::Student& StudentsGroup::_internal_students(int index) const {
  return students_.Get(index);
}
inline const ::Student& StudentsGroup::students(int index) const {
  // @@protoc_insertion_point(field_get:StudentsGroup.students)
  return _internal_students(index);
}
inline ::Student* StudentsGroup::_internal_add_students() {
  return students_.Add();
}
inline ::Student* StudentsGroup::add_students() {
  // @@protoc_insertion_point(field_add:StudentsGroup.students)
  return _internal_add_students();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Student >&
StudentsGroup::students() const {
  // @@protoc_insertion_point(field_list:StudentsGroup.students)
  return students_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_students_2eproto