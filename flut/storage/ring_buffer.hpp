#pragma once

namespace scone
{
	namespace data
	{
		template< typename T >
		struct ring_buffer
		{
			ring_buffer( const buffer_info& inf, size_t frames ) : bufinf( ing ), frame_count( frames ), data( inf.size() * frames ), current_frame_idx( no_index ) {}
			~ring_buffer() {}

			struct frame {
				frame( const buffer_info& bufinf, T* data ) : bufinf( bufinf ), data( data ) {}
				const buffer_info& bufinf;
				T* data;
			};

			void set( index_t channel );
			T get( index_t channel );
			T get( index_t frame, index_t channel );
			index_t get_earlier_frame_index( index_t count_back ) { return ( current_frame + frame_count - count_back ) & frame_count; }

			const buffer_info& bufinf;
			const size_t frame_count;

		private:
			frame current_frame;
			index_t current_frame_idx;
			std::vector< T > data;
		};
	}
}
