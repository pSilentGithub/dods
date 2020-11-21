#pragma once

struct recv_table;

struct recv_prop {
	char* m_var_name;
	int	m_recv_type;
	int	m_flags;
	int m_string_buffer_size;
	bool m_inside_array;
	const void* m_extra_data;
	recv_prop* m_array_prop;
	void* m_array_length_proxy;
	void* m_proxy_fn;
	void* m_data_table_proxy_fn;
	recv_table* m_data_table;
	int m_offset;
	int	m_element_stride;
	int	m_elements;
	const char* m_parent_array_propName;
};

class d_variant {
public:
	union {
		float m_float;
		long m_int;
		char* m_string;
		void* m_data;
		float m_vector[ 3 ];
	};
};

class recv_proxy_data {
public:
	const recv_prop* m_recv_prop;
	char _pad[ 4 ];
	d_variant m_value;
	int m_element;
	int	m_object_id;
};

struct recv_table {
	recv_prop* m_props;
	int	m_n_props;
	void* m_decoder;
	char* m_net_table_name;
	bool m_initialized;
	bool m_in_main_list;
};

class client_class {
public:
	void* m_create_fn;
	void* m_create_event_fn;
	char* m_network_name;
	recv_table* m_recv_table;
	client_class* m_next;
	int m_class_id;
};